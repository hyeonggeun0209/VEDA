#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>
#include <cstring>
#include <srtp2/srtp.h>
#include <arpa/inet.h>  // For htonl(), htons()

#define PORT 5004
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define RTP_HEADER_LEN 12
// #define SRTP_MASTER_KEY_LEN 46  // 30 bytes for master key + 16 bytes for master salt

void initialize_openssl() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
}

SSL_CTX* create_dtls_client_context() {
    const SSL_METHOD* method = DTLS_client_method();
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
    // 클라이언트 인증서와 개인 키 파일 설정 (개발 및 테스트용)
    if (SSL_CTX_use_certificate_file(ctx, "client.crt", SSL_FILETYPE_PEM) <= 0) {
        std::cerr << "Error configuring SSL context with client certificate" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Client certificate loaded successfully." << std::endl;
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "client.key", SSL_FILETYPE_PEM) <= 0) {
        std::cerr << "Error configuring SSL context with client key" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Client key loaded successfully." << std::endl;
    }

    // 서버 인증서 신뢰 설정 (서버의 self-signed 인증서 또는 CA 인증서)
    if (!SSL_CTX_load_verify_locations(ctx, "ca.crt", nullptr)) {
        std::cerr << "Error loading CA certificate to trust store" << std::endl;
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Server certificate loaded successfully." << std::endl;
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
	srtp_t srtp_session; // SRTP 세션 변수 선언
	srtp_err_status_t status; // 상태 변수 선언

    SSL_CTX* ctx = create_dtls_client_context();

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
    struct sockaddr_in servaddr;

    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    } else {
        std::cout << "Socket created successfully." << std::endl;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 소켓을 비연결 UDP 모드로 서버 주소와 연결
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Socket connect failed");
        close(sockfd);
        return -1;
    } else {
        std::cout << "Socket connected to server successfully." << std::endl;
    }

    BIO* bio = BIO_new_dgram(sockfd, BIO_NOCLOSE);
    if (!bio) {
        std::cerr << "Failed to create BIO" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    } else {
        std::cout << "BIO created successfully." << std::endl;
    }

    BIO_ctrl(bio, BIO_CTRL_DGRAM_SET_CONNECTED, 0, &servaddr);

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        std::cerr << "Unable to create SSL structure" << std::endl;
        ERR_print_errors_fp(stderr);
        BIO_free(bio);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
    } else {
        std::cout << "SSL structure created successfully." << std::endl;
    }

    SSL_set_bio(ssl, bio, bio);
    SSL_set_info_callback(ssl, debug_callback);  // 디버그 콜백 추가

    std::cout << "Starting DTLS handshake..." << std::endl;
    int handshake_result = SSL_connect(ssl);
    if (handshake_result <= 0) {
        int ssl_error = SSL_get_error(ssl, handshake_result);
        std::cerr << "DTLS handshake failed with SSL error code: " << ssl_error << std::endl;

        // SSL_get_error()로부터의 상태에 따라 출력
        switch (ssl_error) {
            case SSL_ERROR_NONE:
                std::cerr << "No error occurred." << std::endl;
                break;
            case SSL_ERROR_ZERO_RETURN:
                std::cerr << "The TLS/SSL connection has been closed." << std::endl;
                break;
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
                std::cerr << "The operation did not complete and should be retried." << std::endl;
                break;
            case SSL_ERROR_SYSCALL:
                std::cerr << "A system call error occurred." << std::endl;
                perror("System call error");
                break;
            case SSL_ERROR_SSL:
                std::cerr << "A failure in the SSL library occurred, usually a protocol error." << std::endl;
                ERR_print_errors_fp(stderr);
                break;
            default:
                std::cerr << "An unknown error occurred." << std::endl;
                break;
        }

        // 추가 오류 코드 출력
        unsigned long err;
        while ((err = ERR_get_error()) != 0) {
            char err_msg[256];
            ERR_error_string_n(err, err_msg, sizeof(err_msg));
            std::cerr << "OpenSSL error: " << err_msg << std::endl;
        }

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
    
    // SRTP 키 자료 생성
    unsigned char srtp_key[SRTP_MASTER_KEY_LEN];
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

    if (key_len == 1) {
        std::cout << "SRTP key material exported successfully." << std::endl;

        // SRTP 라이브러리 초기화
        if (srtp_init() != srtp_err_status_ok) {
            std::cerr << "Failed to initialize SRTP library." << std::endl;
            SSL_free(ssl);
            SSL_CTX_free(ctx);
            close(sockfd);
            return -1;
        }

        // SRTP 정책 설정
        srtp_policy_t policy;
        memset(&policy, 0, sizeof(srtp_policy_t));

        srtp_crypto_policy_set_aes_cm_128_hmac_sha1_80(&policy.rtp);
        srtp_crypto_policy_set_aes_cm_128_hmac_sha1_80(&policy.rtcp);

        policy.ssrc.type = ssrc_any_outbound;
        policy.key = srtp_key;
        policy.next = nullptr;

        srtp_t srtp_session;
        srtp_err_status_t status = srtp_create(&srtp_session, &policy);
        if (status != srtp_err_status_ok) {
            std::cerr << "Failed to create SRTP session, error code: " << status << std::endl;
            return -1;
        } else {
            std::cout << "SRTP session created successfully." << std::endl;
        }

        // RTP 헤더 생성 및 데이터 준비
        unsigned char rtp_packet[BUFFER_SIZE];
        memset(rtp_packet, 0, BUFFER_SIZE);

        // RTP 헤더 설정
        rtp_packet[0] = 0x80;  // Version, Padding, Extension, CC
        rtp_packet[1] = 0x60;  // Marker, Payload Type
        uint16_t sequence_number = htons(1);
        memcpy(rtp_packet + 2, &sequence_number, sizeof(sequence_number));
        uint32_t timestamp = htonl(12345);
        memcpy(rtp_packet + 4, &timestamp, sizeof(timestamp));
        uint32_t ssrc = htonl(67890);
        memcpy(rtp_packet + 8, &ssrc, sizeof(ssrc));

        // RTP 페이로드 설정
        const char* payload = "This is a test message for SRTP protection.";
        int payload_len = strlen(payload);
        memcpy(rtp_packet + RTP_HEADER_LEN, payload, payload_len);
        int rtp_packet_len = RTP_HEADER_LEN + payload_len;

        // 데이터 보호 시 버퍼와 길이 확인
        std::cout << "Before SRTP protection, RTP packet length: " << rtp_packet_len << ", payload: " << payload << std::endl;

        // SRTP 데이터 보호
        status = srtp_protect(srtp_session, rtp_packet, &rtp_packet_len);
        if (status != srtp_err_status_ok) { 
            std::cerr << "Failed to protect SRTP data, error code: " << status << std::endl;

            if (status == srtp_err_status_cipher_fail) {
                std::cerr << "Cipher operation failed." << std::endl;
            } else if (status == srtp_err_status_auth_fail) {
                std::cerr << "Authentication failed." << std::endl;
            } else if (status == srtp_err_status_replay_fail) {
                std::cerr << "Replay check failed." << std::endl;
            } else {
                std::cerr << "Unknown SRTP protection error." << std::endl;
            }
        } else {
            std::cout << "SRTP data protected successfully. Protected RTP packet length: " << rtp_packet_len << std::endl;
			// SRTP 데이터를 서버로 전송
			int sent_len = sendto(sockfd, rtp_packet, rtp_packet_len, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
			if (sent_len < 0) {
				perror("Failed to send SRTP data");
			} else {
				std::cout << "SRTP data sent successfully. Length: " << sent_len << std::endl;
			}
        }

        // SRTP 세션 해제
        srtp_dealloc(srtp_session);

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
    return 0;
}
