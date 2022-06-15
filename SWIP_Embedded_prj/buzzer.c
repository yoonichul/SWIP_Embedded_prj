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
#include "IfxGtm_reg.h"


//unsigned int buzzer_cnt = 0;

void initBuzzer(void)
{
    P02_IOCR0.U &= ~(0x1f<< PC3_BIT_LSB_IDX);
    P02_IOCR0.U |=  (0x11<< PC3_BIT_LSB_IDX);
}


void BuzzerLong(unsigned int *buzzer_cnt)                   // �� �������� Buzzer�� �︮�� �Լ�
{
    if(*buzzer_cnt >= 180)                      // cnt���� 180 �̻��� ��� cnt �� �ʱ�ȭ
        buzzer_cnt = 0;
    if(90 <= *buzzer_cnt)                       // cnt���� 90~180 �� ��� Buzzer On
        Buzzer_change_duty_ratio(11800);
    else                                // cnt���� 0~90 �� ��� Buzzer Off
        Buzzer_change_duty_ratio(0);
}

void BuzzerShort(unsigned int *buzzer_cnt)                  // ª�� �������� Buzzer�� �︮�� �Լ�
{
    if(*buzzer_cnt >= 90)                       // cnt���� 90 �̻��� ��� cnt �� �ʱ�ȭ
        buzzer_cnt = 0;
    if(45 <= *buzzer_cnt)                       // cnt���� 45~90 �� ��� Buzzer On
        Buzzer_change_duty_ratio(11800);
    else                                // cnt���� 0~45 �� ��� Buzzer Off
        Buzzer_change_duty_ratio(0);
}

void BuzzerOff(void)                    // Buzzer�� ���� �Լ�
{
    Buzzer_change_duty_ratio(0);
}

void BuzzerOn(void)                     // Buzzer�� �Ѵ� �Լ�
{
    Buzzer_change_duty_ratio(11800);
}
