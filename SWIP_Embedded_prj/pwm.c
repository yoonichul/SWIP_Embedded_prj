/*
 * pwm.c
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Ifx_Types.h"
#include "IfxGtm_reg.h"
#include "pwm.h"
// SCU register
#define LCK_BIT_LSB_IDX             1
#define ENDINIT_BIT_LSB_IDX         0
#define EXIS0_BIT_LSB_IDX           4
#define FEN0_BIT_LSB_IDX            8
#define EIEN0_BIT_LSB_IDX           11
#define INP0_BIT_LSB_IDX            12
#define IGP0_BIT_LSB_IDX            14
// SRC register
#define SRPN_BIT_LSB_IDX            0
#define TOS_BIT_LSB_IDX             11
#define SRE_BIT_LSB_IDX             10

#define DISR_BIT_LSB_IDX            0
#define DISS_BIT_LSB_IDX            1


// GTM register
#define FXCLK_SEL_BIT_LSB_IDX       0
#define EX_FXCLK_BIT_LSB_IDX        22
#define SEL7_BIT_LSB_IDX            14
// TOM0_TGC0_GLB_CTRL register
#define UPEN_CTRL1_BIT_LSB_IDX      18
#define HOST_TRIG_BIT_LSB_IDX       0
// TOM0_TGC0_ENDIS_CTRL register
#define ENDIS_CTRL1_BIT_LSB_IDX     2
// TOM0_TGC0_OUTEN_CTRL register
#define OUTEN_CTRL1_BIT_LSB_IDX     2
// TOM0_CH1_CTRL register
#define SL_BIT_LSB_IDX              11
#define CLK_SRC_SR_BIT_LSB_IDX      12
#define OSB_BIT_LSB_IDX             26
#define TRIG_OUT_BIT_LSB_IDX        24
void initGTM(void)
{
       // Password Access to unlock SCU_WDTSCON0
       SCU_WDTCPU0_CON0.U =((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
       while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);
       //Modify Access to clear ENDINIT
       SCU_WDTCPU0_CON0.U =((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
       while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

       GTM_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable CCY

       // Password Access to unlock SCU_WDTSCON0
       SCU_WDTCPU0_CON0.U =((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) |(1 << ENDINIT_BIT_LSB_IDX);
       while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);
       // Modify Access to set ENDINIT
       SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) |(1 << ENDINIT_BIT_LSB_IDX);
       while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

       while ((GTM_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0);


       // GTM clock configuration
       GTM_CMU_FXCLK_CTRL.U &= ~(0xF << FXCLK_SEL_BIT_LSB_IDX);
       GTM_CMU_CLK_EN.U |= 0x2 << EX_FXCLK_BIT_LSB_IDX;

       GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL1_BIT_LSB_IDX; // TOM channel 1 update enable
       GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL1_BIT_LSB_IDX;
       GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL1_BIT_LSB_IDX;

       GTM_TOM0_CH1_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;
       GTM_TOM0_CH1_CTRL.U |= 0x1 << CLK_SRC_SR_BIT_LSB_IDX;
       GTM_TOM0_CH1_CTRL.U &= ~(0x1 << OSB_BIT_LSB_IDX);
       GTM_TOM0_CH1_CTRL.U &= ~(0x1 << TRIG_OUT_BIT_LSB_IDX);

       GTM_TOM0_CH1_SR0.U = 12500 - 1;                           // PWM freq. = 6250kHz  / 12500 = 500Hz
       GTM_TOM0_CH1_SR1.U = 1250 - 1;
       GTM_TOUTSEL6.U &= ~(0x3 << SEL7_BIT_LSB_IDX);
}



void PWM_trigger(void)
{
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX; // PWM trigger update request signal
}


void change_duty_ratio(unsigned int duty)
{
    GTM_TOM0_CH1_SR1.U = duty - 1;
}
