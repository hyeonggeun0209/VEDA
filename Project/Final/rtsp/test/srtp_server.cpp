#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <srtp2/srtp.h>

#define PORT 5004
#define BUFFER_SIZE 1024
// #define SRTP_MASTER_KEY_LEN 46  // 30 bytes for master key + 16 bytes for master salt

void initialize_openssl() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
}

SSL_CTX* create_dtls_server_context() {
    const SSL_METHOD* method = DTLS_server_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        std::cerr << "Unable to create SSL context" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    // DTLS 1.2 설정
    SSL_CTX_set_min_proto_version(ctx, DTLS1_2_VERSION);
    SSL_CTX_set_max_proto_version(ctx, DTLS1_2_VERSION);
    return ctx;
}

void configure_context(SSL_CTX* ctx) {
    if (SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) <= 0) {
        std::cerr << "Error configuring SSL context with certificate and key" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // 클라이언트 인증서 신뢰 설정 (클라이언트의 self-signed 인증서 또는 CA 인증서)
    if (!SSL_CTX_load_verify_locations(ctx, "ca.crt", nullptr)) {
        std::cerr << "Error loading CA certificate to trust store" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    } else {
        std::cout << "CA certificate loaded successfully." << std::endl;
    }
}

void debug_callback(const SSL* ssl, int where, int ret) {
    if (where & SSL_CB_HANDSHAKE_START) {
        std::cout << "Handshake started..." << std::endl;
    } else if (where & SSL_CB_HANDSHAKE_DONE) {
        std::cout << "Handshake done!" << std::endl;
    } else if (where & SSL_CB_ALERT) {
        std::cout << "SSL alert: " << SSL_alert_type_string_long(ret) << ", " << SSL_alert_desc_string_long(ret) << std::endl;
    } else if (where & SSL_CB_LOOP) {
        std::cout << "SSL state (" << SSL_state_string_long(ssl) << "): " << SSL_state_string(ssl) << std::endl;
    } else if (where & SSL_CB_EXIT) {
        if (ret == 0) {
            std::cerr << "SSL state (" << SSL_state_string_long(ssl) << "): failed" << std::endl;
            ERR_print_errors_fp(stderr);
        } else if (ret < 0) {
            std::cerr << "SSL state (" << SSL_state_string_long(ssl) << "): error" << std::endl;
            ERR_print_errors_fp(stderr);
        }
    }
}

int main() {
    initialize_openssl();

    SSL_CTX* ctx = create_dtls_server_context();

    // SRTP 프로파일 설정
    const char* srtp_profiles = "SRTP_AES128_CM_SHA1_80";
    if (SSL_CTX_set_tlsext_use_srtp(ctx, srtp_profiles) != 0) {
        std::cerr << "Error setting SRTP profiles" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return -1;
    }

    configure_context(ctx);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // 서버 정보 설정
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // 바인딩
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return -1;
    } else {
        std::cout << "Bind successful on port " << PORT << std::endl;
    }

    // SSL 설정
    BIO* bio = BIO_new_dgram(sockfd, BIO_NOCLOSE);
    if (!bio) {
        std::cerr << "Failed to create BIO" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        std::cerr << "Unable to create SSL structure" << std::endl;
        ERR_print_errors_fp(stderr);
        BIO_free(bio);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    SSL_set_bio(ssl, bio, bio);
    SSL_set_info_callback(ssl, debug_callback);

    // 핸드셰이크 시작
    std::cout << "Waiting for DTLS handshake..." << std::endl;
    if (SSL_accept(ssl) <= 0) {
        std::cerr << "DTLS handshake failed" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }
    std::cout << "DTLS handshake successful" << std::endl;

    // 협상된 암호화 스위트 확인
    const char* cipher_suite = SSL_get_cipher(ssl);
    std::cout << "Negotiated Cipher Suite: " << cipher_suite << std::endl;

    // SRTP 프로파일 협상 확인
    const SRTP_PROTECTION_PROFILE *profile = SSL_get_selected_srtp_profile(ssl);
    if (profile != nullptr) {
        std::cout << "Selected SRTP profile: " << profile->name << std::endl;
    } else {
        std::cerr << "Failed to negotiate SRTP profile" << std::endl;
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

// SRTP 키 자료 가져오기
unsigned char srtp_key[SRTP_MASTER_KEY_LEN]; // 총 길이 46바이트: 마스터 키 30바이트 + 솔트 16바이트
int key_len = SSL_export_keying_material(
    ssl,
    srtp_key,
    SRTP_MASTER_KEY_LEN,
    "EXTRACTOR-dtls_srtp",
    strlen("EXTRACTOR-dtls_srtp"),
    nullptr,
    0,
    0
);

// SSL_export_keying_material()의 반환 값이 1이면 성공입니다.
if (key_len == 1) {
    std::cout << "SRTP key material exported successfully." << std::endl;
    // 키 자료를 출력하여 확인 (디버깅 용도로만 사용)
    std::cout << "Exported SRTP Key Material: ";
    for (int i = 0; i < SRTP_MASTER_KEY_LEN; ++i) {
        printf("%02x", srtp_key[i]);
    }
    std::cout << std::endl;
} else {
    std::cerr << "Failed to export keying material for SRTP." << std::endl;

    // 추가된 오류 로그 출력
    unsigned long err_code;
    while ((err_code = ERR_get_error()) != 0) {
        char err_msg[256];
        ERR_error_string_n(err_code, err_msg, sizeof(err_msg));
        std::cerr << "OpenSSL error: " << err_msg << std::endl;
    }

    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sockfd);
    return -1;
}

    // SRTP 프로파일 설정
    srtp_policy_t policy;
    srtp_t srtp_session;
    memset(&policy, 0, sizeof(srtp_policy_t));

    // SRTP 키 설정
    srtp_crypto_policy_set_aes_gcm_128_8_auth(&policy.rtp);
    srtp_crypto_policy_set_aes_gcm_128_8_auth(&policy.rtcp);
    policy.key = srtp_key;
    policy.ssrc.type = ssrc_any_inbound; // 기본 설정

    // SRTP 세션 생성
    srtp_err_status_t status = srtp_create(&srtp_session, &policy);
    if (status != srtp_err_status_ok) {
        std::cerr << "Failed to create SRTP session" << std::endl;
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    }

    std::cout << "SRTP session created successfully." << std::endl;

    // SRTP 암호화된 데이터 수신 및 복호화
    int len = sizeof(cliaddr);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&cliaddr, reinterpret_cast<socklen_t*>(&len));
    if (n < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        ERR_print_errors_fp(stderr);
    } else {
        // SRTP 복호화
        status = srtp_unprotect(srtp_session, buffer, &n);
        if (status != srtp_err_status_ok) {
            std::cerr << "Failed to unprotect SRTP data" << std::endl;
        } else {
            buffer[n] = '\0';
            std::cout << "Client: " << buffer << std::endl;
        }
    }

    // 리소스 해제
    srtp_dealloc(srtp_session);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sockfd);
    return 0;
}