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
#include "register_bit_index.h"
#include "pwm.h"

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
       GTM_CMU_CLK_EN.U |= 0x2 << EN_FXCLK_BIT_LSB_IDX;

       GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL1_BIT_LSB_IDX; // TOM channel 1 update enable
       GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL2_BIT_LSB_IDX; // TOM channel 2 update enable

       GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL1_BIT_LSB_IDX;
       GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL2_BIT_LSB_IDX;

       GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL1_BIT_LSB_IDX;
       GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL2_BIT_LSB_IDX;

       GTM_TOM0_CH1_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;
       GTM_TOM0_CH1_CTRL.U |= 0x1 << CLK_SRC_SR_BIT_LSB_IDX;
       GTM_TOM0_CH1_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);
       GTM_TOM0_CH1_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX);

       GTM_TOM0_CH2_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;
       GTM_TOM0_CH2_CTRL.U |= 0x1 << CLK_SRC_SR_BIT_LSB_IDX;
       GTM_TOM0_CH2_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);
       GTM_TOM0_CH2_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX);

       GTM_TOM0_CH1_SR0.U = 12500 - 1;                           // PWM freq. = 6250kHz  / 12500 = 500Hz
       GTM_TOM0_CH1_SR1.U = 1250 - 1;
       GTM_TOM0_CH2_SR0.U = 12500 - 1;                           // PWM freq. = 6250kHz  / 12500 = 500Hz
       GTM_TOM0_CH2_SR1.U = 1250 - 1;
       GTM_TOUTSEL6.U &= ~(0x3 << SEL7_BIT_LSB_IDX);
       GTM_TOUTSEL6.U &= ~(0x3 << SEL8_BIT_LSB_IDX);

}

// Buzzer GTM init
void initGTM_Buzzer(void)
{
    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    GTM_CLC.U &= ~(1<<DISR_BIT_LSB_IDX);  //ENABLE GTM

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    while((GTM_CLC.U & (1<<DISS_BIT_LSB_IDX)) != 0);

    GTM_CMU_FXCLK_CTRL.U &= ~(0xF << FXCLK_SEL_BIT_LSB_IDX);
    GTM_CMU_CLK_EN.U |= 0x2 << EN_FXCLK_BIT_LSB_IDX;

    GTM_TOM0_TGC1_GLB_CTRL.U |= 0x2 << UPEN_CTRL11_BIT_LSB_IDX; // 11 channel
    GTM_TOM0_TGC1_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL11_BIT_LSB_IDX;
    GTM_TOM0_TGC1_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL11_BIT_LSB_IDX;


    GTM_TOM0_CH11_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;
    GTM_TOM0_CH11_CTRL.U |= 0x1 << CLK_SRC_SR_BIT_LSB_IDX;
    GTM_TOM0_CH11_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);
    GTM_TOM0_CH11_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX);

    GTM_TOUTSEL0.U &= ~(0x3 << 6);

    GTM_TOM0_CH11_SR0.U = 12000-1;

}




void PWM_trigger(void)
{
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;  // PWM trigger update request signal
    GTM_TOM0_TGC1_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;  // Buzzer PWM trigger update request signal
}


void RED_change_duty_ratio(unsigned int duty)
{
    GTM_TOM0_CH1_SR1.U = duty - 1;
}

void BLUE_change_duty_ratio(unsigned int duty)
{
    GTM_TOM0_CH2_SR1.U = duty - 1;

}

void Buzzer_change_duty_ratio(unsigned int duty)
{
    GTM_TOM0_CH11_SR1.U = duty - 1;
}
