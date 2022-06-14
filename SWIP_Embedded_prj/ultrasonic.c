/*
 * ultrasonic.c
 *
 *  Created on: 2022. 6. 14.
 *      Author: user
 */

#include "IfxScuWdt.h"
#include "IfxSrc_reg.h"
#include "IfxStdIf.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxCcu6_reg.h"
#include "register_bit_index.h"
#include "ultrasonic.h"

static unsigned char left_range_valid_flag = 0;
static unsigned char right_range_valid_flag = 0;
unsigned int left_us_range = 0 ;
unsigned int right_us_range = 0 ;
// left_US_setting
void init_left_UltraSonic(void)
{
    P02_IOCR4.U &= ~(0x1F << PC6_BIT_LSB_IDX);
    P00_IOCR4.U &= ~(0x1F << PC4_BIT_LSB_IDX);

    P00_IOCR4.U |= (0x01 << PC4_BIT_LSB_IDX);
    P02_IOCR4.U |= (0x10 << PC6_BIT_LSB_IDX);

    P02_OUT.U &= ~(0x1 << P6_BIT_LSB_IDX );
}

void left_UltraSonic_trigger(void)
{
    P02_OUT.U |= 0x1 << P6_BIT_LSB_IDX;
    left_range_valid_flag = 0;
    CCU60_TCTR4.U |= 0x1 << T12RS_BIT_LSB_IDX;
}

void set_left_range_valid_flag(void)
{
    left_range_valid_flag = 1;
}

void unset_left_range_valid_flag(void)
{
    left_range_valid_flag = 0;
}

unsigned char get_left_range_valid_flag(void)
{
    return left_range_valid_flag;
}

// right_US_setting
void init_right_UltraSonic(void)
{
    P02_IOCR4.U &= ~(0x1F << PC5_BIT_LSB_IDX); //P02_IOCR4.PC5 RESET
    P11_IOCR8.U &= ~(0x1F << PC10_BIT_LSB_IDX); //P11_IOCR8.PC10 RESET

    P11_IOCR8.U |= 0x01 << PC10_BIT_LSB_IDX; //P11_IOCR8.PC10 SET - INPUT
    P02_IOCR4.U |= 0x10 << PC5_BIT_LSB_IDX; //P02_IOCR4.PC5 SET - OUTPUT

    P02_OUT.U  &= ~(0x1 << P5_BIT_LSB_IDX); // P02_5 RESET
}

void right_UltraSonic_trigger(void) //LSY TRIGER SIGNAL
{
    P02_OUT.U |= 0x1 << P5_BIT_LSB_IDX; //P02_5 SET
    right_range_valid_flag = 0;
    CCU60_TCTR4.U |= 0x1 << T12RS_BIT_LSB_IDX;
}

void set_right_range_valid_flag(void)
{
    right_range_valid_flag = 1;
}
void unset_right_range_valid_flag(void)
{
    right_range_valid_flag = 0;
}
unsigned char get_right_range_valid_flag(void)
{
    return right_range_valid_flag;
}

// calculate Ultra_sonic distance
unsigned int calc_left_US_distance(void)
{
    return left_us_range = (((CCU61_T12.B.T12CV * 1000000)/48828) / 58);
}
unsigned int calc_right_US_distance(void)
{
    return left_us_range = (((CCU61_T12.B.T12CV * 1000000)/48828) / 58);
}

