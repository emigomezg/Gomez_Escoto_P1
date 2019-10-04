/*
 * Signal_Generator.h
 *
 *  Created on: Oct 3, 2019
 *      Author: emi_g
 */



#ifndef SIGNAL_GENERATOR_H_
#define SIGNAL_GENERATOR_H_

#include "DAC.h"
#include "MK64F12.h"

typedef enum {SINE,TRIANGLE}waveform_t;

void DAC1_signal_creator(uint8_t wave_form);

void DAC0_signal_creator(uint8_t wave_form);

#endif /* SIGNAL_GENERATOR_H_ */
