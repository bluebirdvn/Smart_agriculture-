/*
 * device_control.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Admin
 */


#include "device_control.h"
#include <stdio.h>
#include <string.h>


struct Device_controller{
    int status[3]; // 0: pump, 1: light, 2: fan

    int (*pump_control)(GPIO_PinState state);
    int (*light_control)(GPIO_PinState state);
    int (*fan_control)(GPIO_PinState state);

    int (*get_status_pump)(void);
    int (*get_status_light)(void);
    int (*get_status_fan)(void);
};

static Device_controller controller_instance;
static int is_initialized = 0;

int pump_control(GPIO_PinState state)
{
	HAL_GPIO_WritePin(GPIOC, PUMP_Pin, state);
	return 0;
}

int light_control(GPIO_PinState state)
{
	HAL_GPIO_WritePin(GPIOC, LIGHT_Pin, state);
	return 0;
}

int fan_control(GPIO_PinState state)
{
	HAL_GPIO_WritePin(GPIOC, FAN_Pin, state);
	return 0;
}

int get_status_pump(void)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, PUMP_Pin);
	return state;
}

int get_status_light(void)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, LIGHT_Pin);
	return state;
}

int get_status_fan(void)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, FAN_Pin);
	return state;
}
void get_device_status(Device_controller *Controller)
{
	if (Controller == NULL) {
		printf("Controller is Null ptr");
		return;
	}
	Controller->status[PUMP] = Controller->get_status_pump();
	Controller->status[LIGHT] = Controller->get_status_light();
	Controller->status[FAN] = Controller->get_status_fan();
}

Device_controller* get_device_controller(void)
{
    if (!is_initialized) {
        controller_instance.pump_control = pump_control;
        controller_instance.light_control = light_control;
        controller_instance.fan_control = fan_control;

        controller_instance.get_status_pump = get_status_pump;
        controller_instance.get_status_light = get_status_light;
        controller_instance.get_status_fan = get_status_fan;

        memset(controller_instance.status, 0, sizeof(controller_instance.status));
        is_initialized = 1;
    }
    return &controller_instance;
}


int* system_controller(int *arr, Device_controller *Controller)
{
	if (Controller == NULL) {
		printf("Controller is Null ptr");
		return NULL;
	}

	get_device_status(Controller);

	for (int i = 0; i < 3; ++i) {
		if (arr[i] != Controller->status[i]) {
			Controller->status[i] = arr[i];
			switch(i) {
				case PUMP:
					Controller->pump_control(Controller->status[i]);
					break;
				case LIGHT:
					Controller->light_control(Controller->status[i]);
					break;
				case FAN:
					Controller->fan_control(Controller->status[i]);
					break;
				default: 
					break;
			}
		}
	}
	
	return Controller->status;
}
