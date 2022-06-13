/*
 * light_sensor.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_


void VADC_light_sensor_init(void);
void VADC_light_sensor_startConversion(void);
unsigned int VADC_light_sensor_readResult(void);




#endif /* LIGHT_SENSOR_H_ */
