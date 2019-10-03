/*
 * DAC.h
 *
 *  Created on: Oct 2, 2019
 *      Author: emi_g
 */

#ifndef DAC_H_
#define DAC_H_

#include "MK64F12.h"

void DAC0_init(void);


void DAC0_out(uint8_t data_out_high,uint8_t data_out_low);

#endif /* DAC_H_ */
