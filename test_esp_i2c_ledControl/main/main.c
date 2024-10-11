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

#include "settings.h"
//I2C CLK 14 - в даташите ESP32 WROVER E 14 - data port - lbos 27
//I2C SDA 12 - в даташите ESP32 WROVER E 12 - clock port - lbos 12

void app_main(void)
{
    ESP_LOGV("APP MAIN control","Start of app_main");
    //настройки i2c
    i2c_config_t pca_control_i2c;
    pca_control_i2c.master.clk_speed = i2c_clk_speed;
    pca_control_i2c.mode = I2C_MODE_MASTER;
    pca_control_i2c.sda_io_num = SDA_PORT;
    pca_control_i2c.scl_io_num = SCL_PORT;
    pca_control_i2c.sda_pullup_en = SDA_PULLUP_STATE;
    pca_control_i2c.scl_pullup_en = SCL_PULLUP_STATE;   
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
    // for (int i = 0;i<4;i++) //cicle info output test
    // {
    //     i2c_addr+=i;
    //     ESP_LOGI(i2c_log, "Адрес i2c %x",i2c_addr);
    // }
}