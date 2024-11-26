#include <SDKAPI/opensdk_defines.h>
#include <SDKAPI/opensdk_device.h>
#include <SDKAPI/opensdk_profile.h>
#include <SDKAPI/opensdk_ptz.h>
#include <SDKAPI/opensdk_record.h>
#include <SDKAPI/opensdk_videoanalytics.h>
#include <SDKAPI/opensdk_videosetup.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <cstring>

#include <sys/stat.h> 
#include <sys/types.h>

#include "test_main.h"

bool lets_start = false;
TEST_MAIN* sunapi_main = TEST_MAIN::get_instance();

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
void recv_event(OPENSDK_INPUT_EVENT eventIn, void *pData) {
  // Handle the input events here
	switch (eventIn) {
		case OPENSDK_APP_SETTING:
        {
            //APP_SETTING* m_setting_ptr = (APP_SETTING*) pData; 
            APP_SETTING* g_setting_ptr = (APP_SETTING*) pData;
            
            if(g_setting_ptr->req->monitor)
            {
                lets_start=true;
                sunapi_main->parse_app_setting_req_data_and_make_res(g_setting_ptr);
				sunapi_main->set_socket(g_setting_ptr->req->id);
            }
			else
			{
				if(strstr(g_setting_ptr->req->data, "StopMonitor") != nullptr)
				{
					lets_start = false;
					sunapi_main->stop_server_push();
					g_setting_ptr->res->pBuff = "Successed";
                	g_setting_ptr->res->pBufLen = strlen(g_setting_ptr->res->pBuff);
				}
			}
            break;
        }
		case OPENSDK_RTSP_METADATA: {			
			sunapi_main->server_push((char*)pData, lets_start);

      		break;
    	}
    default: {
      //debug_message("Unknown event %d occurred\n", eventIn);
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
OPENSDK_ERR_CODE recv_data(void *payload_request, void *payload_response) {
	OPENSDK_PAYLOAD_REQUEST *req_payload;
	OPENSDK_PAYLOAD_RESPONSE *res_payload;
	OPENSDK_ERR_CODE errCode;

	// Initialize local variable
	errCode = OPENSDK_APP_OK;

	// Get the request & response pointer
	req_payload = (OPENSDK_PAYLOAD_REQUEST *)payload_request;
	res_payload = (OPENSDK_PAYLOAD_RESPONSE *)payload_response;

	debug_message("Request from web page: %s and len %d\n", req_payload->pBuff,
					req_payload->pBufLen);

	// Process request & send response

	return errCode;
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
void one_shot(void) {
  	debug_message("one_shot\n");

	std::string NewBestShotUrl(STORAGE_BEST_SHOT_IMAGE);

	struct stat info;

	if (stat(NewBestShotUrl.c_str(), &info) != 0) {
		std::string command = "mkdir " + NewBestShotUrl;
		system(command.c_str());
    } else {
		std::string command = "rm -rf  " + NewBestShotUrl + "*";
		system(command.c_str());
	}
  return;
}
