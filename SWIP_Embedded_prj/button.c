/*
 * button.c
 *
 *  Created on: 2022. 6. 10.
 *      Author: user
 */

#include "button.h"
#include "register_bit_index.h"


void initButton(void) {
    P02_IOCR0.U &= ~(0x1F << PC0_BIT_LSB_IDX);
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);

    P02_IOCR0.U |= 0x02 << PC0_BIT_LSB_IDX;
    P02_IOCR0.U |= 0x02 << PC1_BIT_LSB_IDX;
}
