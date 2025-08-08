/*
 * bh1750.c
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#include "main.h"
#include "BH1750.h"
#include <stdio.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;


static BH1750_device_t BH1750_instance;
static uint8_t is_initialized = 0;

static uint8_t data_handler(BH1750_device_t *BH1750_device)
{
	if (BH1750_device == NULL) {
		printf("BH1750 sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}

	BH1750_device->value = BH1750_device->buffer[0];
	BH1750_device->value = (BH1750_device->value << 8) | (BH1750_device->buffer[1]);
	BH1750_device->value /= 1.2;

	return CODE_SUCCESS;
}

static uint8_t read_lux_sensor(BH1750_device_t *BH1750_device)
{
	if (BH1750_device == NULL) {
		printf("BH1750 sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}

	if (HAL_I2C_Master_Receive(&hi2c1, BH1750_device->address_r, BH1750_device->buffer, sizeof(BH1750_device->buffer), 100) == HAL_OK)
	        return CODE_SUCCESS;
	    return CODE_ERROR_READ_SENSOR;

}

static uint8_t write_cmd_to_lux_sensor(BH1750_device_t *BH1750_device, uint8_t cmd)
{
	if (BH1750_device == NULL) {
		printf("BH1750 sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}

    if (HAL_I2C_Master_Transmit(&hi2c1,BH1750_device->address_w, &cmd, sizeof(cmd), 100) == HAL_OK)
        return CODE_SUCCESS;
    return CODE_ERROR_READ_SENSOR;

}

static uint8_t lux_sensor_init(BH1750_device_t *BH1750_device)
{

	if (BH1750_device == NULL) {
		printf("BH1750 sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}

	if (CODE_SUCCESS != BH1750_device->write_cmd_to_lux_sensor(BH1750_device, CMD_POWER_ON)) return CODE_ERROR_READ_SENSOR;
	if (CODE_SUCCESS != BH1750_device->write_cmd_to_lux_sensor(BH1750_device, CMD_RESET)) return CODE_ERROR_READ_SENSOR;
	if (CODE_SUCCESS != BH1750_device->write_cmd_to_lux_sensor(BH1750_device, CMD_ONE_H_RES_MODE)) return CODE_ERROR_READ_SENSOR;

	return CODE_SUCCESS;
}


BH1750_device_t *bh1750_sensor_init(void)
{
	if (!is_initialized) {
		BH1750_instance.address_w = BH1750_NO_GROUND_ADDR_WRITE;
		BH1750_instance.address_r = BH1750_NO_GROUND_ADDR_READ;

		memset(BH1750_instance.buffer, 0, sizeof(BH1750_instance.buffer));
		BH1750_instance.value = 0;

		BH1750_instance.lux_sensor_init = lux_sensor_init;
		BH1750_instance.read_lux_sensor = read_lux_sensor;
		BH1750_instance.write_cmd_to_lux_sensor = write_cmd_to_lux_sensor;
		BH1750_instance.data_handler = data_handler;

		is_initialized = 1;
	}

	return &BH1750_instance;
}


