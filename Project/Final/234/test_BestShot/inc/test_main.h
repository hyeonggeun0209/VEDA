#ifndef test_main_H_
#define test_main_H_

#include <SDKAPI/opensdk_defines.h>
#include <SDKAPI/opensdk_device.h>
#include <iostream>
#include <fstream>
#include <string.h>


#define RESPONSE_BUFF_SIZE 1024
#define MAX_TIMESTAMP_STRING 100
#define STORAGE_BEST_SHOT_IMAGE "/work/www/htdocs/download/test_BestShot/"

class TEST_MAIN
{
    public:
        TEST_MAIN();
        virtual ~TEST_MAIN();
        static TEST_MAIN* get_instance(void);
        void parse_app_setting_req_data_and_make_res(APP_SETTING* setting_ptr);
        void server_push(char* pData, bool start);
        void set_socket(int socket_id);
        void stop_server_push();
    private:
        static TEST_MAIN* 	main;
        char* responseBuff;
		OPENSDK_DEVICE_DATETIME* responseBuffDateTime;
		int socket;
		void send_data(char* response, 
                           int len);
        void removeOldFiles();
        std::string find_string(std::string Source, std::string tagOpen, std::string tagClose);
        std::string parse_meta_data(char* pData);
        std::string createFileAndSaveData(const std::string& data);
        int count;
         
};

#endif