/*
 * button.h
 *
 *  Created on: 2022. 6. 10.
 *      Author: user
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Ifx_Types.h"
#define BUTTON_RELEASED 1
#define BUTTON_PUSHED 0

void initButton(void);

typedef struct _button {
    volatile Ifx_P_IOCR0 *IOCR_REG;
    volatile Ifx_P_IN *PX_OUT;
    unsigned char prev_state;
} BUTTON;

#endif /* BUTTON_H_ */
