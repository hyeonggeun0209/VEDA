#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 5004
#define SERVER_IP "127.0.0.1"

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

    SSL_CTX* ctx = create_dtls_client_context();
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

    const char* message = "Hello, DTLS Server!";
    int n = SSL_write(ssl, message, strlen(message));
    if (n < 0) {
        std::cerr << "Failed to send message" << std::endl;
        ERR_print_errors_fp(stderr);
    } else {
        std::cout << "Message sent to server" << std::endl;
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sockfd);
    return 0;
}

