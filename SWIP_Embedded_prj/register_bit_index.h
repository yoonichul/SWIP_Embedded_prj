/*
 * register_bit_index.h
 *
 *  Created on: 2022. 6. 14.
 *      Author: user
 */

#ifndef REGISTER_BIT_INDEX_H_
#define REGISTER_BIT_INDEX_H_

#define PC0_BIT_LSB_IDX         3
#define PC1_BIT_LSB_IDX         11
#define PC2_BIT_LSB_IDX         19
#define PC3_BIT_LSB_IDX         27
#define PC4_BIT_LSB_IDX         3
#define PC5_BIT_LSB_IDX         11
#define PC6_BIT_LSB_IDX         19
#define PC7_BIT_LSB_IDX         27
#define PC10_BIT_LSB_IDX        19
#define P0_BIT_LSB_IDX          0
#define P1_BIT_LSB_IDX          1
#define P2_BIT_LSB_IDX          2
#define P3_BIT_LSB_IDX          3
#define P4_BIT_LSB_IDX          4
#define P5_BIT_LSB_IDX          5
#define P6_BIT_LSB_IDX          6
#define P7_BIT_LSB_IDX          7
#define P10_BIT_LSB_IDX         10
// SCU Common register
#define LCK_BIT_LSB_IDX         1
#define ENDINIT_BIT_LSB_IDX     0
// SCU ERS2 register
#define EXIS0_BIT_LSB_IDX       4
#define FEN0_BIT_LSB_IDX        8
#define REN0_BIT_LSB_IDX        9
#define EIEN0_BIT_LSB_IDX       11
#define INP0_BIT_LSB_IDX        12
#define IGP0_BIT_LSB_IDX        14
// SCU ERS3 register
#define EXIS1_BIT_LSB_IDX       20
#define FEN1_BIT_LSB_IDX        24
#define REN1_BIT_LSB_IDX        25
#define EIEN1_BIT_LSB_IDX       27
#define INP1_BIT_LSB_IDX        28
#define IGP1_BIT_LSB_IDX        30
// SRC registers
#define SRPN_BIT_LSB_IDX        0
#define TOS_BIT_LSB_IDX         11
#define SRE_BIT_LSB_IDX         10
// CCU60 register
#define DISR_BIT_LSB_IDX        0
#define DISS_BIT_LSB_IDX        1
#define T12CLK_BIT_LSB_IDX      0
#define T12PRE_BIT_LSB_IDX      3
#define CTM_BIT_LSB_IDX         7
#define T12STR_BIT_LSB_IDX      6
#define T12RS_BIT_LSB_IDX       1
#define INPT12_BIT_LSB_IDX      10
#define ENT12PM_BIT_LSB_IDX     7
#define T12SSC_BIT_LSB_IDX      0
// G4ARPBR Register
#define PRIO0_BIT_LSB_IDX       0
#define CMS0_BIT_LSB_IDX        3
#define ASEN0_BIT_LSB_IDX       24
// G4QMR0 Register
#define ENGT_BIT_LSB_IDX        0
#define TREV_BIT_LSB_IDX        9
#define FLUSH_BIT_LSB_IDX       10
// G4ARBCFG Register
#define ANONC_BIT_LSB_IDX       0
// G4ICLASS0 Register
#define STCS_BIT_LSB_IDX        0
#define CMS_BIT_LSB_IDX         8
// G4CHCTR7 Register
#define ICLSEL_BIT_LSB_IDX      0
#define RESREG_BIT_LSB_IDX      16
#define RESPOS_BIT_LSB_IDX      21
// G4CHASS Register
#define ASSCH6_BIT_LSB_IDX      6
#define ASSCH7_BIT_LSB_IDX      7
// G4RES0 Register
#define RESULT_BIT_LSB_IDX      0
#define VF_BIT_LSB_IDX          31
// G4QINR0 Register
#define REQCHNR_BIT_LSB_IDX 0
// GTM register
#define FXCLK_SEL_BIT_LSB_IDX   0
#define EX_FXCLK_BIT_LSB_IDX    22
#define SEL7_BIT_LSB_IDX        14
#define SEL8_BIT_LSB_IDX        16
// TOM0_TGC0_GLB_CTRL register
#define UPEN_CTRL1_BIT_LSB_IDX  18
#define UPEN_CTRL2_BIT_LSB_IDX  20
#define HOST_TRIG_BIT_LSB_IDX   0
// TOM0_TGC0_ENDIS_CTRL register
#define ENDIS_CTRL1_BIT_LSB_IDX 2
#define ENDIS_CTRL2_BIT_LSB_IDX 4
// TOM0_TGC0_OUTEN_CTRL register
#define OUTEN_CTRL1_BIT_LSB_IDX 2
#define OUTEN_CTRL2_BIT_LSB_IDX 4
// TOM0_CH1_CTRL register
#define SL_BIT_LSB_IDX          11
#define CLK_SRC_SR_BIT_LSB_IDX  12
#define OSB_BIT_LSB_IDX         26
#define TRIG_OUT_BIT_LSB_IDX    24


#endif /* REGISTER_BIT_INDEX_H_ */
