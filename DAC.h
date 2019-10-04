/*
 * DAC.h
 *
 *  Created on: Oct 2, 2019
 *      Author: emi_g
 */

#ifndef DAC_H_
#define DAC_H_

#include "MK64F12.h"
#include <stdio.h>

typedef struct  {
	uint8_t data_high;
	uint8_t data_low;
}dac_data_out_t;

void DAC0_init(void);

void DAC0_out_value(dac_data_out_t);

void DAC1_init(void);

void DAC1_out_value(dac_data_out_t);

void delay(uint16_t);

#endif /* DAC_H_ */
