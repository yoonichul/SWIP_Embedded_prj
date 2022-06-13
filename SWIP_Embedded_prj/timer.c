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

// SCU registers
#define LCK_BIT_LSB_IDX 1
#define ENDINIT_BIT_LSB_IDX 0
#define EXIS0_BIT_LSB_IDX 4
#define FEN0_BIT_LSB_IDX 8
#define EIEN0_BIT_LSB_IDX 11
#define INP0_BIT_LSB_IDX 12
#define IGP0_BIT_LSB_IDX 14

// SRC registers
#define SRPN_BIT_LSB_IDX 0
#define TOS_BIT_LSB_IDX 11
#define SRE_BIT_LSB_IDX 10

#define DISR_BIT_LSB_IDX 0
#define DISS_BIT_LSB_IDX 1
// TCTR0 Register
#define T12CLK_BIT_LSB_IDX 0
#define T12PRE_BIT_LSB_IDX 3
#define CTM_BIT_LSB_IDX 7
// TCTR4 Register
#define T12STR_BIT_LSB_IDX 6
#define T12RS_BIT_LSB_IDX 1
// INP Register
#define INPT12_BIT_LSB_IDX 10
// IEN Register
#define ENT12PM_BIT_LSB_IDX 7

void initCCU60(void) {
    SCU_WDTCPU0_CON0.U =
        ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) |
        (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ;
    SCU_WDTCPU0_CON0.U =
        ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) &
        ~(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ;

    CCU60_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable CCY

    SCU_WDTCPU0_CON0.U =
        ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) |
        (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ;
    SCU_WDTCPU0_CON0.U =
        ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) |
        (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ;

    while ((CCU60_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0)
        ;

    CCU60_TCTR0.U &= ~(0x7 << T12CLK_BIT_LSB_IDX); // f_T12 = f_CCU6 / prescaler
    CCU60_TCTR0.U |=
        0x2 << T12CLK_BIT_LSB_IDX; // f_CCU6 = 50 MHz, prescaler = 1024
    CCU60_TCTR0.U |= 0x1 << T12PRE_BIT_LSB_IDX;

    CCU60_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX);
//    CCU60_T12PR.U = 48828 - 1; // 48,828Hz
    CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX;
    //    CCU60_T12PR.U = 0x17D77;
        CCU60_T12PR.U = 24414 - 1 ; // 48,828Hz

    CCU60_T12.U = 0;

    CCU60_INP.U &= ~(0x3 << INPT12_BIT_LSB_IDX);
    CCU60_IEN.U |= 0x1 << ENT12PM_BIT_LSB_IDX;

    SRC_CCU6_CCU60_SR0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_CCU6_CCU60_SR0.U |= 0x0B << SRPN_BIT_LSB_IDX; // set priority 0x0B

    SRC_CCU6_CCU60_SR0.U &= ~(0x3 << TOS_BIT_LSB_IDX);

    SRC_CCU6_CCU60_SR0.U |= 0x1 << SRE_BIT_LSB_IDX;

    CCU60_TCTR4.U |= 0x1 << T12RS_BIT_LSB_IDX;
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
