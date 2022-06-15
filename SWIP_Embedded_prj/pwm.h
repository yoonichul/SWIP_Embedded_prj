/*
 * pwm.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef PWM_H_
#define PWM_H_



void initGTM(void);
void PWM_trigger(void);
void RED_change_duty_ratio(unsigned int duty);
void BLUE_change_duty_ratio(unsigned int duty);
void initGTM_Buzzer(void);
void Buzzer_change_duty_ratio(unsigned int duty);

#endif /* PWM_H_ */
