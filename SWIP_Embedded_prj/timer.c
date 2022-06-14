/*
 * timer.c
 *
 *  Created on: 2022. 6. 8.
 *      Author: user
 */
#include "timer.h"
#include "IfxCcu6_reg.h"
#include "IfxScuWdt.h"
#include "IfxSrc_reg.h"
#include "IfxStdIf.h"
#include "Ifx_Types.h"
#include "register_bit_index.h"


void CCU61_start(void)
{
    CCU61_TCTR4.U = 0x1 << T12RS_BIT_LSB_IDX;
}
void CCU61_T12_stop(void)
{
    CCU61_TCTR4.B.T12RR = 0x1;
}
void CCU61_T12_reset(void)
{
    CCU61_TCTR4.B.T12RES = 0x1;
}
void initCCU60(void) {

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    CCU60_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    while((CCU60_CLC.U & (1<<DISS_BIT_LSB_IDX)) != 0);

    CCU60_TCTR0.U &= ~( 0x7<< T12CLK_BIT_LSB_IDX);
    CCU60_TCTR0.U |= 0x2 << T12CLK_BIT_LSB_IDX;
    //CCU60_TCTR0.U |= 0x1 << T12PRE_BIT_LSB_IDX;




    CCU60_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX);

    CCU60_T12PR.U = 125-1;
    CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;

    CCU60_TCTR2.B.T12SSC = 0x1;

    CCU60_T12.U = 0;

    CCU60_INP.U &= ~(0x3 << INPT12_BIT_LSB_IDX);
    CCU60_IEN.U |= 0x1 << ENT12PM_BIT_LSB_IDX;


    SRC_CCU6_CCU60_SR0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_CCU6_CCU60_SR0.U |= 0x0B << SRPN_BIT_LSB_IDX;

    SRC_CCU6_CCU60_SR0.U &= ~(0x3 << TOS_BIT_LSB_IDX);

    SRC_CCU6_CCU60_SR0.U |= 0x1 << SRE_BIT_LSB_IDX;

    //CCU60_TCTR4.U |= 0x1 << T12RS_BIT_LSB_IDX;

}



void initCCU61(void) {
    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    CCU61_CLC.U &= ~(1 << DISR_BIT_LSB_IDX);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);

    SCU_WDTCPU0_CON0.U= ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 <<ENDINIT_BIT_LSB_IDX );
    while((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    while((CCU61_CLC.U & (1<<DISS_BIT_LSB_IDX)) != 0);

    CCU61_TCTR0.U &= ~( 0x7<< T12CLK_BIT_LSB_IDX);
    CCU61_TCTR0.U |= 0x2 << T12CLK_BIT_LSB_IDX;

    CCU61_TCTR0.U |= 0x1 << T12PRE_BIT_LSB_IDX;

    CCU61_T12PR.U = 10000-1;
    CCU61_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;

    CCU61_T12.U = 0;



}

void change_freq(unsigned int status) {
    if (status) {
        CCU60_T12PR.U = 48828 - 1; // 48,828Hz
        CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;
    } else {
        CCU60_T12PR.U = 12207 - 1; // 12,207Hz
        CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;
    }
}
