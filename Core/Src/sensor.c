/*
 * sensor.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Admin
 */

#include <stdio.h>
#include "sensor.h"
#include "main.h"
#include "aht30.h"
#include <string.h>
#include "bh1750.h"


struct Sensor{

	uint8_t moisture_raw;

	aht30_handle_t *aht_30_handler;
	uint32_t temperature_raw;
	float temperature_s;
	uint32_t humidity_raw;
	uint8_t humidity_s;

	BH1750_device_t *bh1750_handler;
	uint16_t lux_sensor;

	uint32_t (*read_moisture_sensor)(Sensor *sensor);
	uint32_t (*read_temperature_humidity_sensor)(Sensor *sensor);
	uint32_t (*read_light_sensor)(Sensor *sensor);
};

static Sensor sensor_instance;
static int is_initialized = 0;


uint32_t moisture_sensor(Sensor *sensor)
{
	if (sensor == NULL) {
		printf("sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	sensor->moisture_raw = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	return CODE_SUCCESS;
}

uint32_t temperature_humidity_sensor(Sensor *sensor)
{
	if (sensor == NULL) {
		printf("sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}
	int i = 5;
	while (i--) {
		if (aht30_read_temperature_humidity(sensor->aht_30_handler, &sensor->temperature_raw, &sensor->temperature_s, &sensor->humidity_raw, &sensor->humidity_s) == 0) {
				printf("Read temperature and humidity from aht30 sensor successfully.");
				break;
			}
	}
	return CODE_SUCCESS;
}

uint32_t light_sensor(Sensor *sensor)
{
	if (sensor == NULL) {
		printf("sensor is NULL ptr");
		return CODE_ERROR_NULL_PTR;
	}

	if (CODE_SUCCESS != sensor->bh1750_handler->lux_sensor_init) return CODE_ERROR_INIT_SENSOR;
	if (CODE_SUCCESS != sensor->bh1750_handler->read_lux_sensor) return CODE_ERROR_READ_SENSOR;
	if (CODE_SUCCESS != sensor->bh1750_handler->data_handler) return CODE_ERROR_READ_SENSOR;

	sensor->lux_sensor = sensor->bh1750_handler->value;

	return CODE_SUCCESS;
}



Sensor* sensor_init(void)
{
	if (!is_initialized) {
		sensor_instance.read_moisture_sensor = moisture_sensor;
		sensor_instance.read_temperature_humidity_sensor = temperature_humidity_sensor;
		sensor_instance.read_light_sensor = light_sensor;

		sensor_instance.aht_30_handler = app_aht30_init();
		sensor_instance.humidity_raw = 0;
		sensor_instance.humidity_s = 0;
		sensor_instance.temperature_raw = 0;
		sensor_instance.temperature_s = 0;

		sensor_instance.bh1750_handler = bh1750_sensor_init();
		sensor_instance.lux_sensor = 0;

		is_initialized = 1;
	}

	return &sensor_instance;
}



