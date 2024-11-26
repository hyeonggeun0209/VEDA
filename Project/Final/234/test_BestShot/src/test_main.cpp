#include "test_main.h"

#include <ctime>
#include <sstream>
#include <vector>
#include <cstdio>

std::vector<std::string> fileList;

TEST_MAIN* TEST_MAIN::main = NULL;

TEST_MAIN::TEST_MAIN()
{
    responseBuffDateTime = new OPENSDK_DEVICE_DATETIME();
    memset(responseBuffDateTime, 0, sizeof(OPENSDK_DEVICE_DATETIME));
	responseBuff = new char[RESPONSE_BUFF_SIZE];
    memset(responseBuff, 0, sizeof(RESPONSE_BUFF_SIZE));
    socket = 0;
    count = 0;
    fileList.clear();
}

TEST_MAIN::~TEST_MAIN()
{
    if(responseBuffDateTime)
    {
        delete responseBuffDateTime;
        responseBuffDateTime = NULL;
    }
	if(responseBuff)
    {
        delete responseBuff;
        responseBuff = NULL;
    }
    fileList.clear();
}

TEST_MAIN* TEST_MAIN::get_instance(void)
{
    if(main == NULL)
    {
		main = new TEST_MAIN();
    }

    return main;
}

void TEST_MAIN::stop_server_push()
{
    socket = 0;
    count = 0;
    
    std::string NewBestShotUrl(STORAGE_BEST_SHOT_IMAGE);
    std::string command = "rm -rf  " + NewBestShotUrl + "*";
    system(command.c_str());
    fileList.clear();
}

void TEST_MAIN::parse_app_setting_req_data_and_make_res(APP_SETTING* setting_ptr)
{
    char response[100] = "";
	unsigned int ch = 0;
    
    snprintf(response,MAX_TIMESTAMP_STRING,"Start Monitor Data");
    
    *responseBuff = ch;
	memcpy(responseBuff+sizeof(UINT32_N), response, strlen(response));
    
    setting_ptr->res->pBuff = responseBuff; 
    setting_ptr->res->pBufLen = strlen(response)+sizeof(UINT32_N); //: channel value 

    if(socket != 0)
    {
        send_data(responseBuff, setting_ptr->res->pBufLen);
    }
}

void TEST_MAIN::set_socket(int socket_id)
{
    socket = socket_id;
}

std::string TEST_MAIN::find_string(std::string Source, std::string tagOpen, std::string tagClose)
{
    size_t startPos = Source.find(tagOpen);
    if (startPos != std::string::npos) {
        startPos += tagOpen.length();

        size_t endPos = Source.find(tagClose, startPos);

        if (endPos != std::string::npos) {
            std::string Data = Source.substr(startPos, endPos - startPos);
            return Data;
        }
    }
    return "";
}


void TEST_MAIN::removeOldFiles() {
    if (fileList.size() >= 10) {
        std::string NewBestShotUrl(STORAGE_BEST_SHOT_IMAGE);
		std::string command = "rm -rf  " + NewBestShotUrl + "*";
		system(command.c_str());
        fileList.clear();
    }
}

std::string TEST_MAIN::createFileAndSaveData(const std::string& data) {

    removeOldFiles();

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream oss;
std::string fileName = "file_" + std::to_string(localTime->tm_year + 1900) + '_'
        + std::to_string(localTime->tm_mon + 1) + '_'
        + std::to_string(localTime->tm_mday) + '_'
        + std::to_string(localTime->tm_hour) + '_'
        + std::to_string(localTime->tm_min) + '_'
        + std::to_string(localTime->tm_sec) + ".txt";
    oss << STORAGE_BEST_SHOT_IMAGE << fileName;

    std::string filename = oss.str();

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << data;
        outFile.close();
        

        fileList.push_back(filename);

        return std::string("/download/test_BestShot/" + fileName);
    } else {
        return "";
    }
}

std::string TEST_MAIN::parse_meta_data(char* pData)
{
    std::string metadata(pData);

    std::string imageData = find_string(metadata, std::string("<tt:ImageRef>"), std::string("</tt:ImageRef>"));
    
    if (!imageData.empty()) {

        std::cout << "url : " << imageData << std::endl;

        std::string BestShotUrl = "/tmp/"+ imageData;
        std::string NewBestShotUrl(STORAGE_BEST_SHOT_IMAGE);
        std::string command = "cp " + BestShotUrl + " " + NewBestShotUrl;
        system(command.c_str());

        std::string target("download/");
        size_t pos = metadata.find(std::string(target));
        if (pos != std::string::npos) {
            metadata.insert(pos + target.length(), std::string("test_BestShot/"));
            
            std::string metadataNewPath = createFileAndSaveData(metadata);
            if(!metadataNewPath.empty())
            {
                count = 10;
                return metadataNewPath;
            }
            
        }
    }
    count ++;
    return std::string("Not have best shot meta data\n");
}

void TEST_MAIN::server_push(char* pData, bool start)
{
    if(!start)
        return ;
    
    std::string data = parse_meta_data(pData);
    if(count < 10 && data.length() > 1020)
    {
        return;
    }

    memset(responseBuff, 0, RESPONSE_BUFF_SIZE);

    *responseBuff = 0;
	memcpy(responseBuff+sizeof(UINT32_N), data.c_str(), data.length());
    
    int BufLen = data.length() + sizeof(UINT32_N); //: channel value 

    if(socket != 0)
    {
        send_data(responseBuff, BufLen);
        count = 0;
    }
}

/**
*@ ********************************************************************
*@ Name           : send_data                                         *
*@ Description    : send response to client                           *
*@ Arguments      : response[IN]: Response to client                  *
*@                : len[IN]     : Length of response                  *
*@ Return Value   : NILL                                              *
*@ Notes          :                                                   *
*@ Change History :                                                   *
*@ ********************************************************************
**/
void TEST_MAIN::send_data(char* response, 
                           int len)
{
    // OPENSDK_NETWORK_PACKET pPacket;
    
    // //Create network packet
    // pPacket.buff      = response;
    // pPacket.size      = len;
    // pPacket.client_id = client_id;
    
    //Send response to client
	OPENSDK::EVENT::send_event(OPENSDK_EVENT_SERVERPUSH, &socket, (void*)response, len);

    return;
}