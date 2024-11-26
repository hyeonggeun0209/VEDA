#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <cstring>

void handleOpenSSLError() {
    ERR_print_errors_fp(stderr);
}

int main() {
    const char *message = "Hello, OpenSSL!";
    unsigned char encrypted[256] = {0};
    unsigned char decrypted[256] = {0};
    int encrypted_length, decrypted_length;

    RSA *rsa_keypair = RSA_new();
    BIGNUM *bne = BN_new();
    if (!BN_set_word(bne, RSA_F4) || !RSA_generate_key_ex(rsa_keypair, 2048, bne, NULL)) {
        std::cerr << "Error generating RSA keypair" << std::endl;
        handleOpenSSLError();
        return 1;
    }

    encrypted_length = RSA_public_encrypt(strlen(message), (unsigned char*)message, encrypted, rsa_keypair, RSA_PKCS1_OAEP_PADDING);
    if (encrypted_length == -1) {
        std::cerr << "Error encrypting message" << std::endl;
        handleOpenSSLError();
        return 1;
    }
    std::cout << "Encrypted message successfully!" << std::endl;

    decrypted_length = RSA_private_decrypt(encrypted_length, encrypted, decrypted, rsa_keypair, RSA_PKCS1_OAEP_PADDING);
    if (decrypted_length == -1) {
        std::cerr << "Error decrypting message" << std::endl;
        handleOpenSSLError();
        return 1;
    }

    std::cout << "Decrypted message: " << decrypted << std::endl;

    RSA_free(rsa_keypair);
    BN_free(bne);
    return 0;
}

