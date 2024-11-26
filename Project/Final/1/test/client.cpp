#include <curl/curl.h>
#include <iostream>
#include <string>

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
        std::string data;
        std::cout << "Enter data to send securely: ";
        std::getline(std::cin, data);

        curl_easy_setopt(curl, CURLOPT_URL, "https://localhost:4433");
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);  
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);                   
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);                   
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
       // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);                          

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}

