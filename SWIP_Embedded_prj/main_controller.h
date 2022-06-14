/*
 * main_cotroller.h
 *
 *  Created on: 2022. 6. 14.
 *      Author: user
 */

#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "adc.h"
#include "button.h"
#include "interrupt.h"
#include "led.h"
#include "timer.h"
#include "ASCLIN_Shell_UART.h"
#include "light_sensor.h"
#include "pwm.h"
#include "register_bit_index.h"
#include "ultrasonic.h"
void controller_init(void);
void doWork(void);


void idle_func(void);
void BCA_SCENE_func(void);
void SCC_SCENE_func(void);
void TUNNEL_SCENE_func(void);

#endif /* MAIN_CONTROLLER_H_ */
