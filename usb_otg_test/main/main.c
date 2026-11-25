/***************************************************************************************************************************************
∎ CONTEXT: 
	⟹ ESP-S3 USB OTG Test Using and LED on the HMI Custom Hardware
***************************************************************************************************************************************/
#include <stdio.h>
#include <esp_system.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include "esp_log.h" 

/*******************************************************************************************************************************/
#define LED_PIN 41
/*******************************************************************************************************************************
ENUMERATION: LEDC Defs
********************************/
// PWM Configuration Constants
#define LEDC_TIMER            LEDC_TIMER_0
#define LEDC_MODE             LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL_LED      LEDC_CHANNEL_1   
// Duty Cycle Constants for Buzzer
#define DUTY_5_PERCENT        (410)    
#define DUTY_10_PERCENT       (819)
#define DUTY_50_PERCENT       (4095)
#define DUTY_25_PERCENT       (2047) 
#define DUTY_20_PERCENT       (1638) 
#define DUTY_100_PERCENT      (8191)
/*******************************************************************************************************************************/

/********************************************************************************************************************************
FUNCTIONS: PROTOTYPES
**********************/
void setupPWMForLED();
void heartbeat();

/*******************************************************************************************************************************
FUNCTION: THE MAIN APPLICATION
*****************************/
void app_main(void)
{

    setupPWMForLED();

    while (1) {
        heartbeat();
        printf("Led blinking\n");
        ESP_LOGI("LED", "Led Blinking...\n");
        //vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
 
/*******************************************************************************************************************************/

 
/*******************************************************************************************************************************/
// Configure PWM for LED
void setupPWMForLED() {
    printf("setting led as PWM...\n");

    // Configure timer FIRST
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Then configure channel
    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_CHANNEL_LED,
        .duty       = 0,
        .gpio_num   = LED_PIN,
        .speed_mode = LEDC_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER
    };
    ledc_channel_config(&ledc_channel);
}

 /**
 * @brief heart beat.
 */
void heartbeat() {
  for (int i = 0; i < 2; i++) {		
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_LED, DUTY_100_PERCENT);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_LED);
    vTaskDelay(pdMS_TO_TICKS(130));
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_LED, 0);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_LED);
    vTaskDelay(pdMS_TO_TICKS(130)); 				
  }    	   
}
/*******************************************************************************************************************************/