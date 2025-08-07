/*
 * sensor.h
 *
 *  Created on: Aug 7, 2025
 *      Author: Admin
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include <stdint.h>

typedef struct Sensor Sensor;

uint32_t moisture_sensor(Sensor *sensor);

uint32_t temperature_moisture_sensor(Sensor *sensor);

uint32_t light_sensor(Sensor *sensor);

Sensor* sensor_init(void);


#endif /* INC_SENSOR_H_ */
