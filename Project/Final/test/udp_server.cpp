#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 5004
#define BUFFER_SIZE 1024

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
}

void debug_callback(const SSL* ssl, int where, int ret) {
    if (where & SSL_CB_HANDSHAKE_START) {
        std::cout << "Handshake started..." << std::endl;
    } else if (where & SSL_CB_HANDSHAKE_DONE) {
        std::cout << "Handshake done!" << std::endl;
    } else if (where & SSL_CB_ALERT) {
        std::cout << "SSL alert: " << SSL_alert_type_string_long(ret) << ", " << SSL_alert_desc_string_long(ret) << std::endl;
    }
}

int main() {
    initialize_openssl();

    SSL_CTX* ctx = create_dtls_server_context();
    configure_context(ctx);

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

    // 데이터 수신
    socklen_t len = sizeof(cliaddr);
    int n = SSL_read(ssl, buffer, BUFFER_SIZE);
    if (n < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        ERR_print_errors_fp(stderr);
    } else {
        buffer[n] = '\0';
        std::cout << "Client: " << buffer << std::endl;
    }

    // 리소스 해제
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sockfd);
    return 0;
}

