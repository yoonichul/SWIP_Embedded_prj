/*
 * ultrasonic.h
 *
 *  Created on: 2022. 6. 14.
 *      Author: user
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

// left_US_setting
void init_left_UltraSonic(void);
void left_UltraSonic_trigger(void);
void set_left_range_valid_flag(void);
void unset_left_range_valid_flag(void);
unsigned char get_left_range_valid_flag(void);

// right_US_setting
void init_right_UltraSonic(void);
void right_UltraSonic_trigger(void);
void set_right_range_valid_flag(void);
void unset_right_range_valid_flag(void);
unsigned char get_right_range_valid_flag(void);

// calculate Ultra_sonic distance
unsigned int calc_left_US_distance(void);
unsigned int calc_right_US_distance(void);



#endif /* ULTRASONIC_H_ */
