/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
//#include "Ifx_Types.h"
//#include "IfxCpu.h"
//#include "IfxScuWdt.h"
////#include "adc.h"
//#include "button.h"
//#include "interrupt.h"
//#include "led.h"
//#include "timer.h"
//#include "ASCLIN_Shell_UART.h"
//#include "light_sensor.h"
//#include "pwm.h"
//#include "register_bit_index.h"
//#include "ultrasonic.h"
#include "main_controller.h"

//static unsigned int adc_result = 0;
//unsigned int button_status = BUTTON_RELEASED; // 1 :  released , 0: pushed
extern unsigned int left_us_range;
extern unsigned int right_us_range;
extern unsigned char scenario_button;
IfxCpu_syncEvent g_cpuSyncEvent = 0;
__interrupt(0x0B) __vector_table(0)
 void CCU60_T12_ISR(void)
{
    // end of 10us Trig
    // GPIO P02.6 --> LOW
    P02_OUT.U &= ~(0x1 << P6_BIT_LSB_IDX);
    P02_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX);
}
__interrupt(0x0A) __vector_table(0)
 void ERU1_ISR(void)
{
    if((P00_IN.U &(0x1 << P4_BIT_LSB_IDX)) != 0)
    {
        CCU61_start();
    }
    else
    {
        CCU61_T12_stop();
        left_us_range = calc_left_US_distance();
        set_left_range_valid_flag();
        CCU61_T12_reset();
    }

}
__interrupt(0x09) __vector_table(0)
void ERU2_ISR(void)
{
    if((P11_IN.U & (0x1 << 10)) !=0)
    {
        CCU61_start();
    }
    else
    {
        CCU61_T12_stop();
        right_us_range = calc_right_US_distance();
        set_right_range_valid_flag();
        CCU61_T12_reset();
    }
}

__interrupt(0x07) __vector_table(0)
void ERU3_ISR(void)
{
    scenario_button+=1; // LED GREEN D10 (RGB)
    if(!scenario_button && scenario_button % 4 == 0)
    {
         scenario_button = 0;
     }
}

int core0_main(void) {

    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);


    controller_init();
    while (1) {
        doWork();
//        if(left_us_range == 100)  P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;
//        if( (P02_IN.U & (0x1<<P0_BIT_LSB_IDX)) == 0)
//        {
//            P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;    // LED RED D9 (RGB)
//            P10_OUT.U |= (0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
//            P10_OUT.U |= (0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)
//        }
//        for(unsigned int i = 0; i < 10000000; i++ );
//        right_UltraSonic_trigger();
//        while(get_right_range_valid_flag() == 0);
//        if(right_us_range > 10 )
//        {
//            P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;
//        }
//        else
//        {
//            P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
//
//        }
//        left_UltraSonic_trigger();
//        while(get_left_range_valid_flag() == 0);
//        if(left_us_range > 10 )
//        {
//            P10_OUT.U |= (0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
//        }
//        else
//        {
//            P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX);
//
//        }

//        runShellInterface();
//        Print_UART_INT(right_us_range);
    }
    return (1);
}
