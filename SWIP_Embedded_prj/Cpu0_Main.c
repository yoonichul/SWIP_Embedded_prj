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
#include "main_controller.h"


extern unsigned int left_us_range;
extern unsigned int right_us_range;
extern unsigned char scenario_button;
unsigned int buzzer_cnt = 0;

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
        buzzer_cnt++;
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
    scenario_button+=1;
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

    }
    return (1);
}
