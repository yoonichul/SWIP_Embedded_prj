/*
 * interrupt.c
 *
 *  Created on: 2022. 6. 8.
 *      Author: user
 */

#include "interrupt.h"
#include "IfxScuWdt.h"
#include "IfxSrc_reg.h"
#include "IfxStdIf.h"
#include "Ifx_Types.h"
// SCU ERS2 registers
#define LCK_BIT_LSB_IDX 1
#define ENDINIT_BIT_LSB_IDX 0
#define EXIS0_BIT_LSB_IDX 4
#define FEN0_BIT_LSB_IDX 8
#define REN0_BIT_LSB_IDX 9
#define EIEN0_BIT_LSB_IDX 11
#define INP0_BIT_LSB_IDX 12
#define IGP0_BIT_LSB_IDX 14
// SCU ERS3 registers
#define EXIS1_BIT_LSB_IDX 20
#define FEN1_BIT_LSB_IDX 24
#define REN1_BIT_LSB_IDX 25
#define EIEN1_BIT_LSB_IDX 27
#define INP1_BIT_LSB_IDX 28
#define IGP1_BIT_LSB_IDX 30

// SRC registers
#define SRPN_BIT_LSB_IDX 0
#define TOS_BIT_LSB_IDX 11
#define SRE_BIT_LSB_IDX 10

void initERU(void) {
    SCU_EICR1.U &= ~(0x7 << EXIS0_BIT_LSB_IDX);
    SCU_EICR1.U |= (0x1 << EXIS0_BIT_LSB_IDX);

    SCU_EICR1.U |= 0x1 << REN0_BIT_LSB_IDX;
    //    SCU_EICR1.U |= 0x1 << FEN0_BIT_LSB_IDX;
    SCU_EICR1.U |= 0x1 << EIEN0_BIT_LSB_IDX;

    SCU_EICR1.U &= ~(0x7 << INP0_BIT_LSB_IDX);

    SCU_IGCR0.U &= ~(0x3 << IGP0_BIT_LSB_IDX);
    SCU_IGCR0.U |= 0x1 << IGP0_BIT_LSB_IDX;

    SRC_SCU_SCU_ERU0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU0.U |= (0x0A << SRPN_BIT_LSB_IDX);

    SRC_SCU_SCU_ERU0.U &= ~(0x03 << TOS_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU0.U |= 0x1 << SRE_BIT_LSB_IDX;
}

void initERU02(void) {
    SCU_EICR1.U &= ~(0x7 << EXIS1_BIT_LSB_IDX);
    SCU_EICR1.U |= (0x2 << EXIS1_BIT_LSB_IDX);

    SCU_EICR1.U |= 0x1 << FEN1_BIT_LSB_IDX;
    SCU_EICR1.U |= 0x1 << REN1_BIT_LSB_IDX;

    SCU_EICR1.U |= 0x1 << EIEN1_BIT_LSB_IDX;

    SCU_EICR1.U &= ~(0x7 << INP1_BIT_LSB_IDX);
    SCU_EICR1.U |= 0X1 << INP1_BIT_LSB_IDX;

    SCU_IGCR0.U &= ~(0x3 << IGP1_BIT_LSB_IDX);
    SCU_IGCR0.U |= 0x1 << IGP1_BIT_LSB_IDX;

    SRC_SCU_SCU_ERU1.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU1.U |= (0x0C << SRPN_BIT_LSB_IDX);

    SRC_SCU_SCU_ERU1.U &= ~(0x03 << TOS_BIT_LSB_IDX);
    SRC_SCU_SCU_ERU1.U |= 0x1 << SRE_BIT_LSB_IDX;
}
