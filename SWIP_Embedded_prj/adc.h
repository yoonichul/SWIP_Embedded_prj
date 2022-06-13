/*
 * adc.h
 *
 *  Created on: 2022. 6. 10.
 *      Author: user
 */

#ifndef ADC_H_
#define ADC_H_
void initVADC(void);
void VADC_startConversion(void);
unsigned int VADC_readResult(void);
#endif /* ADC_H_ */
