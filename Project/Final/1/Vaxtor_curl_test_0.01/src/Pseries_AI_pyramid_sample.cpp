#include <fcntl.h>
#include <SDKAPI/opensdk_videosetup.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <curl/curl.h>
#include <openssl/opensslv.h>
#include <sstream>
#include <utility>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdarg.h>
#include <vector>
#include <dlfcn.h>

//#define JPEG_FILE_PATH        "/mnt/1/Vaxtor_curl_test_0.01/html/"
#define JPEG_FILE_PATH        "/mnt/opensdk/html/VaxALPR/"
// #define JPEG_FILE_NAME_FORMAT "testCGI_%lu%03lu.%s"
#define PRE_DEBUG "[DEBUG]_%lu%03lu.%s"
#define JPEG_FILE_NAME_FORMAT "index.%s"
#define NAME_MAX         255

#define CHECK_CURL_FUNC(func) \
    do {\
        ret_curl_code = func;\
        if(ret_curl_code != CURLE_OK) {\
            fprintf(stderr, "[%s:%d] curl_easy_strerror[%s] ret_curl_code[%d] \n", __FILE__, __LINE__, curl_easy_strerror(ret_curl_code), ret_curl_code);\
        }\
    } while (0)

std::vector<std::string> cookies;
char* globalCookieData = nullptr;
struct MemoryStruct {
    char *memory;
    size_t size;
};

/**
*@ ********************************************************************
*@ Name           : recv_event                                        *
*@ Description    : Receives input event from camera SDK              *
*@ Arguments      : eventIn[IN]: Input event type                     *
*@                : pData[IN]  : Data for input event                 *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/

void CreateDebugFile()
{
    char file_name[NAME_MAX + 1] = { 0, };
    snprintf(file_name, sizeof(file_name), JPEG_FILE_PATH JPEG_FILE_NAME_FORMAT,"html");
    std::ofstream fd(file_name);
	fd.close();
};

std::string formatString(const std::string& format, va_list args) {
    va_list argsCopy;
    va_copy(argsCopy, args);
    int size = vsnprintf(nullptr, 0, format.c_str(), argsCopy);
    va_end(argsCopy);

    std::string buffer(size + 1, '\0');
    vsnprintf(&buffer[0], buffer.size(), format.c_str(), args);
    buffer.pop_back();

    return buffer;
}

bool DebugPush(const std::string& buff, ...)
{
    char file_name[NAME_MAX + 1] = { 0, };
    snprintf(file_name, sizeof(file_name), JPEG_FILE_PATH JPEG_FILE_NAME_FORMAT,"html");

    if (buff.empty())
    {
        return false;
    }

    std::ofstream fd(file_name, std::ios::out | std::ios::app);

    if (!fd.is_open())
    {
        printf("open for \"%s\" has failed\n", file_name);
        return false;
    }

    printf("AnhVH7 ----> FileName = [%s], data = %s\n", file_name, buff.c_str());

    va_list args;
    va_start(args, buff);
    std::string result = formatString(buff, args);
    va_end(args);

    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time_t);
    fd << std::string(now_tm->tm_zone)+ "[" + std::to_string(now_tm->tm_hour) + ":" + std::to_string(now_tm->tm_min) + ":" + std::to_string(now_tm->tm_sec) + "] "+ result;
    fd << result;
    fd.close();

    return true;
};


void recv_event(OPENSDK_INPUT_EVENT eventIn, void* pData)
{
    //Handle the input events here
    switch(eventIn) {
        default:
        {
            //DebugPush("[Vaxtor]Unknown event %d occurred\n", eventIn);
            break;
        }
    }

    return;
}
/**
*@ ********************************************************************
*@ Name           : recv_data                                         *
*@ Description    : Receives data from camera SDK                     *
*@ Arguments      : payload_request[IN]: Request from web page        *
*@                : payload_response[OUT]  : Response to web page     *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
OPENSDK_ERR_CODE recv_data(void *payload_request,
                           void *payload_response)
{
    OPENSDK_PAYLOAD_REQUEST*  req_payload;
    OPENSDK_PAYLOAD_RESPONSE* res_payload;
    OPENSDK_ERR_CODE          errCode;
    
    //Initialize local variable
    errCode = OPENSDK_APP_OK;
    
    //Get the request & response pointer
    req_payload = (OPENSDK_PAYLOAD_REQUEST*)payload_request;
    res_payload = (OPENSDK_PAYLOAD_RESPONSE*)payload_response;
    
    DebugPush("[Vaxtor]Request from web page: %s and len %d\n", 
                req_payload->pBuff, req_payload->pBufLen);
    
    //Process request & send response
    
    return errCode;
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    reinterpret_cast<std::string*>(userp)->append(contents, size * nmemb);
    return size * nmemb;
}

size_t HeaderCallback(char *buffer, size_t size, size_t nitems, std::vector<std::string> *cookies)
{
    std::string header(buffer, size * nitems);
    //DebugPush("header: %s\n", header.c_str());
    // Find "Set-Cookie" header and extract cookie value
    if (header.find("Set-Cookie:") != std::string::npos) {
        size_t startPos = header.find(":") + 2; // start position of cookie value
        size_t endPos = header.find(";"); // end position of cookie value
        if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos) {
            std::string cookie = header.substr(startPos, endPos - startPos);
            cookies->push_back(cookie);
        }
    }
    return size * nitems;
}

void displayCookies(CURL *curl) {
    CURLcode res;
    struct curl_slist *cookiesList;
    
    res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookiesList);
    if (res == CURLE_OK && cookiesList) {
       DebugPush("Cookies:\n");
        struct curl_slist *cookie = cookiesList;
        while (cookie) {
            DebugPush("%s\n",cookie->data);
            cookie = cookie->next;
        }
        DebugPush("end of Cookies:\n");
        curl_slist_free_all(cookiesList);
    } else {
        DebugPush("Failed to retrieve cookie list.\n");
    }
}

void displayAndSaveCookies(CURL *curl) {
    CURLcode res;
    struct curl_slist *cookies;
    
    res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
    if (res == CURLE_OK && cookies) {
        DebugPush("Cookies:\n");
        struct curl_slist *cookie = cookies;
        std::string cookieData;
        while (cookie) {
            cookieData += cookie->data;
            cookieData += "\n";
            cookie = cookie->next;
            DebugPush("%s", cookieData.c_str());
        }
        curl_slist_free_all(cookies);
        
        if (globalCookieData)
            free(globalCookieData);
        
        globalCookieData = strdup(cookieData.c_str());
    } else {
        DebugPush("Failed to retrieve cookie list.\n");
    }
}

std::string extractCookieFromHeader(const std::string& header) {
    std::string cookie;
    std::size_t found = header.find("Set-Cookie:");
    if (found != std::string::npos) {
        std::size_t start = found + std::string("Set-Cookie:").length();
        std::size_t end = header.find("\r\n", start);
        cookie = header.substr(start, end - start);
    }
    return cookie;
}

bool DoLogin(CURL* curl, const std::string& productKey, std::string& errorMessage)
{
    DebugPush("AnhVH7 -----> [%s][%s][%d], --------->\n", __FILE__, __FUNCTION__, __LINE__);

    curl_version_info_data *version_data = curl_version_info(CURLVERSION_NOW);
    DebugPush("AnhVH7 -----> libcurl version: %s\n", version_data->version);
    DebugPush("AnhVH7 -----> libcurl host: %s\n", version_data->host);
    DebugPush("AnhVH7 -----> libcurl ssl_version: %s\n", version_data->ssl_version);
    DebugPush("AnhVH7 -----> Compiled with OpenSSL version: %s\n", OPENSSL_VERSION_TEXT);
    printf(OPENSSL_VERSION_TEXT);

    long returnCode = -1;
    CURLcode res = CURLE_OK;
    char errbuf[CURL_ERROR_SIZE];
    std::string readBuffer;
    CURLcode ret_curl_code;
    char* encoded =  curl_easy_escape(curl, productKey.c_str(), 0);
	
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_CAINFO, "/mnt/1/Vaxtor_curl_test_0.01/libs/cacert.pem"));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_COOKIELIST, "ALL"));
    // Do login
    std::string url = (std::string) "https://licensing.vaxtor.com/" + "ems/v710/ws/loginByProductKey.ws?productKey=" + encoded;
	DebugPush("[Vaxtor]url -> %s\n", url.c_str());												
    curl_free(encoded);
	
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_URL, url.c_str()));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L));
	errbuf[0] = 0;
	
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L));
	struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "User-Agent:Hanwha");
	CHECK_CURL_FUNC(curl_easy_setopt(curl,CURLOPT_HTTPHEADER, chunk));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_POST, 1));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ""));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer));

    //COOKIE
    // std::vector<std::string> cookies;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &cookies);
    //end of COOKIE

	res = curl_easy_perform(curl);

    if (res != 0)
	{
		DebugPush("[Vaxtor]Error login to license server: %i\n", res);
		if (errbuf[0] != 0)
        {
            errorMessage = std::string("Error login to license server: ") + std::string(errbuf);
			DebugPush("[Vaxtor]Curl: %s\n", errbuf);
		}
		else
		{
            errorMessage = std::string("Error login to license server: ") + std::string(curl_easy_strerror(res));
			DebugPush("[Vaxtor]Curl: %s\n", curl_easy_strerror(res));            
		}
	}
	else
	{
		 curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &returnCode);
	}

	DebugPush("[Vaxtor]Return code was: %li\n", returnCode);
	DebugPush("[Vaxtor]Read buffer is: %s\n", readBuffer.c_str());

    // //START GET COOKIE
    // if (!cookies.empty())
    // {
    //     DebugPush("Start get cookies:\n");
    //     for (const auto& cookie : cookies)
    //     {
    //         DebugPush("%s\n", cookie.c_str());
    //     }
    //     DebugPush("End get Cookies\n");
    // }
    // else
    // {
    //     DebugPush("[Vaxtor] No cookies received.\n");
    // }
    // //END GET COOKIE

    // displayCookies(curl);
    displayAndSaveCookies(curl);

    // std::size_t cookiePos = readBuffer.find("Set-Cookie:");
    // if (cookiePos != std::string::npos) {
    //     std::string cookie = readBuffer.substr(cookiePos);
    //     DebugPush("Cookie: %s\n", cookie);
    // } else {
    //    DebugPush("No cookie found!\n");
    // }

	if (chunk != NULL)    
		curl_slist_free_all(chunk);

    if (returnCode == 400)
    {
        errorMessage = readBuffer;
        return false;
    }

    return returnCode == 200;
}

bool CheckAID(CURL* curl, const std::string& aid)
{
    DebugPush("AnhVH7 -----> [%s][%s][%d], --------->\n", __FILE__, __FUNCTION__, __LINE__);
    if (aid.empty())
        return false;
    long returnCode = -1;
	CURLcode res = CURLE_OK;
	char errbuf[CURL_ERROR_SIZE];
	std::string readBuffer;
    CURLcode    ret_curl_code;
    
    std::string url = (std::string) "https://licensing.vaxtor.com/" + "ems/v710/ws/activation/" + aid + ".ws";
    errbuf[0] = 0;
	DebugPush("[Vaxtor]url -> %s\n", url.c_str());

    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_URL, url.c_str()));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L));
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "User-Agent:Hanwha");
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk));
    CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_POST, 0));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback));
	CHECK_CURL_FUNC(curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer));

    //COOKIE
    // std::string cookieHeader = "Cookie: ";
    // struct curl_slist *cookiesList = NULL;
    // for (const auto& cookie : cookies)
    // {
    //     DebugPush("Cookies for CheckAID request:\n");
    //     cookieHeader += cookie + "; ";
    //     DebugPush("%s\n", cookieHeader.c_str());
    //     cookiesList = curl_slist_append(cookiesList, cookieHeader.c_str());
    // }
    // curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesList);

    std::string cookieHeader = "";
    for (const auto& cookie : cookies) {
        cookieHeader += cookie + "; Path=/ems; HttpOnly";
    }
    DebugPush("%s\n", cookieHeader.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookieHeader.c_str());
    //end of COOKIE

    // displayCookies(curl);
    // displayAndSaveCookies(curl);
    // curl_easy_setopt(curl, CURLOPT_COOKIE, globalCookieData);

	res = curl_easy_perform(curl);	
    if (res != 0)
	{
		DebugPush("[Vaxtor]Error downloading activation: %i\n", res);
		if (errbuf[0] != 0)
        {
			DebugPush("[Vaxtor]Curl: %s\n", errbuf);
		}
		else
		{
			DebugPush("[Vaxtor]Curl: %s\n", curl_easy_strerror(res));            
		}
	}
	else
	{
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &returnCode);
	}

	DebugPush("[Vaxtor]Return code was: %ld\n", returnCode);
	DebugPush("[Vaxtor]Read buffer is: %s\n", readBuffer.c_str());

    if (chunk != NULL)    
		curl_slist_free_all(chunk);
        // curl_slist_free_all(cookiesList);

    if (returnCode != 200)
    {
        DebugPush("[Vaxtor]Error checking AID\n");
        return false;
    }

    return true;
}

/**
*@ ********************************************************************
*@ Name           : one_shot                                          *
*@ Description    : called to initialize application                  *
*@ Arguments      : N/A                                               *
*@ Return Value   : N/A                                               *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
void one_shot(void)
{
    CreateDebugFile();
    
    DebugPush("[Vaxtor]\033[41m============================== one_shot Start ==============================\033[0m\n");
    printf("[Vaxtor]\033[41m============================== one_shot Start ==============================\033[0m\n");

	std::string productKey = "fc7eb45d-bad2-40b2-82f9-802ecba8de07";
	std::string errorMessage = "";
    if (productKey.empty())
    {
        DebugPush("[Vaxtor]Product key can't be empty\n");
        return;
    }

	CURL* curl = curl_easy_init();
	if (!curl)
	{
		DebugPush("[Vaxtor]Error initializing comunication with the licensing server\n");
		return;
	}

    if (!DoLogin(curl, productKey, errorMessage))
    {
        DebugPush("AnhVH7 -----> [%s][%s][%d], --------->\n", __FILE__, __FUNCTION__, __LINE__);
        DebugPush("[Vaxtor]Login failed\n");
        curl_easy_cleanup(curl);        
        return;
    }

	CheckAID(curl, "705c2907-28b2-485e-bc30-12dc3d4290f9");

  	DebugPush("[Vaxtor]\033[41m============================== one_shot End ==============================\033[0m\n");
    printf("[Vaxtor]\033[41m============================== one_shot End ==============================\033[0m\n");

    return;
}


