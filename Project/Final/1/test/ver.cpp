#include <iostream>
#include <curl/curl.h>
#include <openssl/opensslv.h>

int main() {
    curl_version_info_data *version_data = curl_version_info(CURLVERSION_NOW);
    std::string curl_version = version_data->version;

    std::string openssl_version = OPENSSL_VERSION_TEXT;

    std::cout << "curl version: " << curl_version << std::endl;
    std::cout << "OpenSSL version: " << openssl_version << std::endl;

    return 0;
}

