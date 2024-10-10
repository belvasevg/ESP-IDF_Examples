#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define GREEN GPIO_NUM_4
#define RED GPIO_NUM_18
//static unsigned long counter=1;


void app_main(void)
{
    gpio_reset_pin(RED);
    gpio_set_direction(RED,GPIO_MODE_DEF_OUTPUT);
    gpio_set_pull_mode(RED,GPIO_FLOATING);
    gpio_reset_pin(GREEN);
    gpio_set_direction(GREEN,GPIO_MODE_DEF_OUTPUT);
    gpio_set_pull_mode(GREEN,GPIO_FLOATING);
    
    while(1)
    {
        
        gpio_set_level(RED,0x01);
        vTaskDelay(250/portTICK_PERIOD_MS);
        gpio_set_level(RED,0x00);
        vTaskDelay(250/portTICK_PERIOD_MS);
        gpio_set_level(GREEN,0x01);
        vTaskDelay(250/portTICK_PERIOD_MS);
        gpio_set_level(GREEN,0x00);
        vTaskDelay(250/portTICK_PERIOD_MS);
    }
}

