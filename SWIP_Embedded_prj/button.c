/*
 * button.c
 *
 *  Created on: 2022. 6. 10.
 *      Author: user
 */

#include "button.h"

#define PC0_BIT_LSB_IDX 3
#define PC1_BIT_LSB_IDX 11
#define PC2_BIT_LSB_IDX 19
#define PC3_BIT_LSB_IDX 27
#define PC5_BIT_LSB_IDX 11
#define PC7_BIT_LSB_IDX 27
#define P0_BIT_LSB_IDX 0
#define P1_BIT_LSB_IDX 1
#define P2_BIT_LSB_IDX 2
#define P3_BIT_LSB_IDX 3
#define P5_BIT_LSB_IDX 5
#define P7_BIT_LSB_IDX 7

void initButton(void) {
    P02_IOCR0.U &= ~(0x1F << PC0_BIT_LSB_IDX);
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);

    P02_IOCR0.U |= 0x02 << PC0_BIT_LSB_IDX;
    P02_IOCR0.U |= 0x02 << PC1_BIT_LSB_IDX;
}
