/*
 * device_control.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Admin
 */


#include "device_control.h"

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

Device_controller controller = {
    .pump_control = pump_control,
    .light_control = light_control,
    .fan_control = fan_control,
    .get_status_pump = get_status_pump,
    .get_status_light = get_status_light,
    .get_status_fan = get_status_fan
};


int system_controller(int *arr, int *ret) {
	GPIO_PinState state[3];
	for (int i = 0; i < 3; ++i) {
		if (arr[i] == 1){

		}
	}
}
