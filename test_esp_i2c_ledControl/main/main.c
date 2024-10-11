#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2c_master.h"
#include "driver/i2c_slave.h"
#include "esp_log.h"
//I2C CLK 14 - в даташите ESP32 WROVER E 14 - data port
//I2C SDA 12 - в даташите ESP32 WROVER E 12 - clock port

//unsigned int arr_adds = {0x21,0x22,0x23,0x24};
static int i2c_addr = 0x21;
static const char* i2c_log = "I2C control";

void app_main(void)
{
    ESP_LOGV("APP MAIN control","Start of app_main");
    //настройки i2c
    i2c_config_t pca_control_i2c;
    pca_control_i2c.master.clk_speed = 100000;
    pca_control_i2c.mode = I2C_MODE_MASTER;
    pca_control_i2c.sda_io_num = 12;
    pca_control_i2c.scl_io_num = 27;
    pca_control_i2c.sda_pullup_en = 0x01;
    pca_control_i2c.scl_pullup_en = 0x01;   
    pca_control_i2c.clk_flags = 0;
    vTaskDelay(500/portTICK_PERIOD_MS);
    esp_err_t err = i2c_param_config(I2C_NUM_0,&pca_control_i2c);
    if (err!=ESP_OK)
    {
        ESP_LOGE(i2c_log,"I2C bus #%d setup error: #%d",I2C_NUM_0,err);
    }

    err = i2c_driver_install(I2C_NUM_0,pca_control_i2c.mode,0,0,0);
    if (err == ESP_OK)
    {
        ESP_LOGI(i2c_log,"I2C success!\nBus: %d\nGPIO:\nSDA: %d\nSCL: %d",I2C_NUM_0,pca_control_i2c.sda_io_num,pca_control_i2c.scl_io_num);
    }
    else{
        ESP_LOGE(i2c_log,"I2C INIT ERROR!\nBus:%d\nERROR:%d",I2C_NUM_0,err);
    }
    vTaskDelay(500/portTICK_PERIOD_MS);
    for (int i = 0;i<4;i++)
    {
        i2c_addr+=i;
        ESP_LOGI(i2c_log, "Адрес i2c %x",i2c_addr);
    }
    
}