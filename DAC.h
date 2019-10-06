/*
 * DAC.h
 *
 *  Created on: Oct 2, 2019
 *      Author: emi_g
 */

#ifndef DAC_H_
#define DAC_H_

#include "MK64F12.h"

typedef struct  {
	uint8_t data_high;
	uint8_t data_low;
}dac_data_out_t;

/*This function will activate the DAC0 clock gate and enable DAC0.*/
void DAC0_init(void);

/*This function will send a value to DAC0. It receives a structure
 * data type with low and high values*/
void DAC0_out_value(dac_data_out_t);

/*This function will activate the DAC1 clock gate and enable DAC1.*/
void DAC1_init(void);

/*This function will send a value to DAC1. It receives a structure
 * data type with low and high values*/
void DAC1_out_value(dac_data_out_t);

#endif /* DAC_H_ */
