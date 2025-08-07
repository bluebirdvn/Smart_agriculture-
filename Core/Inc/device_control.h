/*
 * device_control.h
 *
 *  Created on: Aug 7, 2025
 *      Author: Admin
 */

#ifndef INC_DEVICE_CONTROL_H_
#define INC_DEVICE_CONTROL_H_

#include "main.h"

typedef enum {
    PUMP = 0,
    LIGHT,
    FAN
} DeviceIndex;

typedef struct Device_controller Device_controller;

Device_controller* get_device_controller(void);

int pump_control(GPIO_PinState state);

int light_control(GPIO_PinState state);

int fan_control(GPIO_PinState state);

int* system_controller(int *arr, Device_controller *Controller);

int get_status_pump(void);

int get_status_light(void);

int get_status_fan(void);

void get_device_status(Device_controller *Controller);




#endif /* INC_DEVICE_CONTROL_H_ */
