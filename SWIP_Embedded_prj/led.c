/*
 * led.c
 *
 *  Created on: 2022. 6. 10.
 *      Author: user
 */

#include "led.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Ifx_Types.h"
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
void initRGBLED(void) {
//    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
//    P10_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX);
    P10_IOCR0.U &= ~(0x1F << PC3_BIT_LSB_IDX);
    P10_IOCR4.U &= ~(0x1F << PC5_BIT_LSB_IDX);
    P02_IOCR4.U &= ~(0x1F << PC7_BIT_LSB_IDX);

//    P10_IOCR0.U |= 0x10 << PC1_BIT_LSB_IDX;
//    P10_IOCR0.U |= 0x10 << PC2_BIT_LSB_IDX;
    P10_IOCR0.U |= 0x10 << PC3_BIT_LSB_IDX;
    P10_IOCR4.U |= 0x10 << PC5_BIT_LSB_IDX;
    P02_IOCR4.U |= 0x10 << PC7_BIT_LSB_IDX;
}

void initLED_PWM(void)
{
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX);
    P10_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX);

    P10_IOCR0.U |= 0x11 << PC1_BIT_LSB_IDX;
    P10_IOCR0.U |= 0x11 << PC2_BIT_LSB_IDX;
}


void RGB_rotate(void) {
    static unsigned int led_color_flag = 0;
    switch (led_color_flag) {
    case 0: {
        P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;    // LED RED D9 (RGB)
        P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
        P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)
        break;
    }
    case 1: {
        P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); // LED RED D9 (RGB)
        P10_OUT.U |= 0x1 << P5_BIT_LSB_IDX;    // LED GREEN D10 (RGB)
        P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)
        break;
    }
    case 2: {
        P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); // LED RED D9 (RGB)
        P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
        P10_OUT.U |= 0x1 << P3_BIT_LSB_IDX;    // LED BLUE D11 (RGB)
        break;
    }
    case 3: {
        P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); // LED RED D9 (RGB)
        P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)
        P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
        break;
    }
    }
    led_color_flag = (++led_color_flag) % 4;
}
