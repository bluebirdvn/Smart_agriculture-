/*
 * sensor.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Admin
 */

#include <stdio.h>
#include "sensor.h"
#include "main.h"
#include <string.h>

struct Sensor{
	uint32_t data[4];

	uint32_t (*read_moisture_sensor)(Sensor *sensor);
	uint32_t (*read_temperature_moisture_sensor)(Sensor *sensor);
	uint32_t (*read_light_sensor)(Sensor *sensor);
};


uint32_t moisture_sensor(Sensor *sensor)
{
	if (sensor == NULL) {
		printf("sensor is NULL ptr");
		return -1;
	}

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	sensor->data[0] = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	return CODE_SUCCESS;
}

uint32_t temperature_moisture_sensor(Sensor *sensor);

uint32_t light_sensor(Sensor *sensor);


static Sensor sensor_instance;
static int is_initialized = 0;

Sensor* sensor_init(void)
{
	if (!is_initialized) {
		sensor_instance.read_moisture_sensor = moisture_sensor;
		sensor_instance.read_temperature_moisture_sensor = temperature_moisture_sensor;
		sensor_instance.read_light_sensor = light_sensor;

		memset(sensor_instance.data, 0, sizeof(sensor_instance.data));
		is_initialized = 1;
	}

	return &sensor_instance;
}



