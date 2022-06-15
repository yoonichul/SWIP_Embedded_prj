/*
 * buzzer.h
 *
 *  Created on: 2022. 6. 15.
 *      Author: user
 */

#ifndef BUZZER_H_
#define BUZZER_H_



void initBuzzer(void);
void BuzzerLong(unsigned int *buzzer_cnt);
void BuzzerShort(unsigned int *buzzer_cnt);
void BuzzerOff(void);
void BuzzerOn(void);


#endif /* BUZZER_H_ */
