/*
 * buzzer.c
 *
 *  Created on: 2022. 6. 15.
 *      Author: user
 */



#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "pwm.h"
#include "register_bit_index.h"
#include "buzzer.h"

unsigned int buzzer_cnt = 0;

void initBuzzer(void)
{
    P02_IOCR0.U &= ~(0x1f<< PC3_BIT_LSB_IDX);
    P02_IOCR0.U |=  (0x11<< PC3_BIT_LSB_IDX);
}

void BUZZER_FUNCTION(unsigned int bp)
{
    if(bp==1)
    {
        buzzer_cnt=0;
        P02_IOCR0.U &=  ~(0x11<< PC3_BIT_LSB_IDX);
    }
    else{
        if(buzzer_cnt==1)
        {
            P02_IOCR0.U |=  (0x11<< PC3_BIT_LSB_IDX);
        }
        else if(buzzer_cnt==300)
        {
            P02_IOCR0.U ^=  (0x11<< PC3_BIT_LSB_IDX);
        }
        else if(buzzer_cnt>=bp)
        {
            buzzer_cnt=0;
        }
    }
}

void BuzzerLong(void)                   // 긴 간격으로 Buzzer를 울리는 함수
{
    if(buzzer_cnt >= 180)                      // cnt값이 180 이상일 경우 cnt 값 초기화
        buzzer_cnt = 0;
    if(90 <= buzzer_cnt)                       // cnt값이 90~180 일 경우 Buzzer On
        Buzzer_change_duty_ratio(11800);
    else                                // cnt값이 0~90 일 경우 Buzzer Off
        Buzzer_change_duty_ratio(0);
}

void BuzzerShort(void)                  // 짧은 간격으로 Buzzer를 울리는 함수
{
    if(buzzer_cnt >= 90)                       // cnt값이 90 이상일 경우 cnt 값 초기화
        buzzer_cnt = 0;
    if(45 <= buzzer_cnt)                       // cnt값이 45~90 일 경우 Buzzer On
        Buzzer_change_duty_ratio(11800);
    else                                // cnt값이 0~45 일 경우 Buzzer Off
        Buzzer_change_duty_ratio(0);
}

void BuzzerOff(void)                    // Buzzer를 끄는 함수
{
    Buzzer_change_duty_ratio(0);
}

void BuzzerOn(void)                     // Buzzer를 켜는 함수
{
    Buzzer_change_duty_ratio(11800);
}
