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
	// OpenSSL 1.1.0 이상에서 DTLS 1.2를 명시적으로 설정하기 위해
    SSL_CTX_set_min_proto_version(ctx, DTLS1_2_VERSION);
    SSL_CTX_set_max_proto_version(ctx, DTLS1_2_VERSION);
    return ctx;
}

int main() {
    initialize_openssl();

    SSL_CTX* ctx = create_dtls_client_context();
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

    int sockfd;
    struct sockaddr_in servaddr;

    // 소켓 생성
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    BIO* bio = BIO_new_dgram(sockfd, BIO_NOCLOSE);
    if (!bio) {
        std::cerr << "Failed to create BIO" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        close(sockfd);
        return -1;
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
    }

    SSL_set_bio(ssl, bio, bio);

    std::cout << "Starting DTLS handshake..." << std::endl;
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "DTLS handshake failed" << std::endl;

        // 오류 코드 가져오기
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

