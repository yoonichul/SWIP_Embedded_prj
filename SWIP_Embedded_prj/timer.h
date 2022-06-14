/*
 * timer.h
 *
 *  Created on: 2022. 6. 8.
 *      Author: user
 */

#ifndef TIMER_H_
#define TIMER_H_

void initCCU60(void);
void initCCU61(void);
void change_freq(unsigned int status);
void CCU61_start(void);
void CCU61_T12_stop(void);
void CCU61_T12_reset(void);

#endif /* TIMER_H_ */
