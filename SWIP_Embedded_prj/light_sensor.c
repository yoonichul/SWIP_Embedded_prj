/*
 * light_sensor.c
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxVadc_reg.h"
#include "Ifx_Types.h"
#include "light_sensor.h"

#define LCK_BIT_LSB_IDX 1
#define ENDINIT_BIT_LSB_IDX 0
#define EXIS0_BIT_LSB_IDX 4
#define FEN0_BIT_LSB_IDX 8
#define EIEN0_BIT_LSB_IDX 11
#define INP0_BIT_LSB_IDX 12
#define IGP0_BIT_LSB_IDX 14
// SRC Register
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
// G4ARPBR Register
#define PRIO0_BIT_LSB_IDX 0
#define CMS0_BIT_LSB_IDX 3
#define ASEN0_BIT_LSB_IDX 24
// G4QMR0 Register
#define ENGT_BIT_LSB_IDX 0
#define TREV_BIT_LSB_IDX 9
#define FLUSH_BIT_LSB_IDX 10
// G4ARBCFG Register
#define ANONC_BIT_LSB_IDX 0
// G4ICLASS0 Register
#define STCS_BIT_LSB_IDX 0
#define CMS_BIT_LSB_IDX 8
// G4CHCTR7 Register
#define ICLSEL_BIT_LSB_IDX 0
#define RESREG_BIT_LSB_IDX 16
#define RESPOS_BIT_LSB_IDX 21
// G4CHASS Register
#define ASSCH6_BIT_LSB_IDX 6
#define ASSCH7_BIT_LSB_IDX 7
// G4RES0 Register
#define RESULT_BIT_LSB_IDX 0
#define VF_BIT_LSB_IDX 31
// G4QINR0 Register
#define REQCHNR_BIT_LSB_IDX 0



void VADC_light_sensor_init(void)
{
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) |(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);

    VADC_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable CCY

    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0);
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0);
    while ((VADC_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0);

    VADC_G4_ARBPR.U |= 0x3 << PRIO0_BIT_LSB_IDX;
    VADC_G4_ARBPR.U &= ~(0x1 << CMS0_BIT_LSB_IDX);
    VADC_G4_ARBPR.U |= 0x1 << ASEN0_BIT_LSB_IDX;

    VADC_G4_QMR0.U &= ~(0x3 << ENGT_BIT_LSB_IDX);
    VADC_G4_QMR0.U |= 0x1 << ENGT_BIT_LSB_IDX;
    VADC_G4_QMR0.U |= 0x1 << FLUSH_BIT_LSB_IDX;

    VADC_G4_ARBCFG.U &= ~(0x3 << ANONC_BIT_LSB_IDX);
    VADC_G4_ARBCFG.U |= 0x3 << ANONC_BIT_LSB_IDX;

    VADC_G4_ICLASS0.U &= ~(0x7 << CMS_BIT_LSB_IDX);

    VADC_G4_CHCTR6.U |= 0x1 << RESPOS_BIT_LSB_IDX;
    VADC_G4_CHCTR6.U &= ~(0x3 << ICLSEL_BIT_LSB_IDX);
    VADC_G4_CHCTR6.U &= ~(0xF << RESREG_BIT_LSB_IDX);

    VADC_G4_CHASS.U |= 0x1 << ASSCH6_BIT_LSB_IDX;
}


void VADC_light_sensor_startConversion(void)
{
    VADC_G4_QINR0.U |= 0x06;
    VADC_G4_QMR0.U |= 0x1 << TREV_BIT_LSB_IDX;
}

unsigned int VADC_light_sensor_readResult(void){
    unsigned int result;
    while ((VADC_G4_RES0.U & (0x1 << VF_BIT_LSB_IDX)) == 0);
    result = VADC_G4_RES0.U & (0xFFF << RESULT_BIT_LSB_IDX);
    return result;
}

