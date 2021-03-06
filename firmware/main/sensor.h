#ifndef __BRUCON_SENSOR_H
#define __BRUCON_SENSOR_H

#include "driver/gpio.h"
#include "driver/adc.h"
#include "soc/adc_channel.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void init_sensor (void);

uint32_t getSensor(void);
void sensorheat(int on);
void waitsensor();
void calAlcTask();
#endif



