/**
 * WiFi OTA Driver for ESP32-S3-WROOM-1-N8R8
 * Developer: Eric Mulwa
 * Date: 06/10/2025
 * Last Modified: 06/10/2025
 * wifi_ota.h
 */

#ifndef WIFI_OTA_H
#define WIFI_OTA_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_crt_bundle.h"  
#include "string.h"
#include <time.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "freertos/event_groups.h"
#include "nvs.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_mac.h"
#include "esp_vfs_fat.h"

/*******************************************************************************************************************************
FIRMWARE: METADATA
*******************/ 
#define FIRMWARE_TITLE    "Hmi_ota_firmware"
#define FIRMWARE_VERSION  "v1.22"

/** NOTE: Firmware Versions for easy tracking
*			NEXT v1.23, v1.24.....v1.29         
*			NEXT v1.30, v1.31.....v1.39
*			NEXT v1.40, v1.41.....v1.49
*/ 

/** NOTE: Always remember to update the CMakeLists.txt to current version
*         and Leave the project folder still as Hmi_ota_firmware_v1.0, this does not affect anything
*/

/*********************************************************************************************************************************
FUNCTIONS: PROTOTYPES
********************/
/* External */
extern bool wifi_connected;
extern bool ota_flag;

/* Internal */
void initialize_nvs();
esp_err_t _http_event_handler(esp_http_client_event_t *evt);
void perform_secure_ota_update();
// Thingsboard GET
esp_err_t tb_client_event_handler(esp_http_client_event_handle_t evt);
bool get_thingsboard_fw_info(void);
// Querry if OTA is needed
bool is_ota_required(void);
// perform ota
bool perform_ota();
// CHIP MAC {TB Access Token}
uint32_t otagetChipId();
void otagetChipIdString(char *device_token, size_t size);
// check the running partition
void running_partition();
void tb_report_ota_status(const char *state, int progress, const char *error);
/*******************************************************************************************************************************/

#endif /* WIFI_OTA_H */