/*
 * PIT_SG.h
 *
 *  Created on: Oct 4, 2019
 *      Author: emi_g
 */

#ifndef SM_SG_H_
#define SM_SG_H_

#include "PIT.h"
#include "NVIC.h"
#include "MK64F12.h"
#include "DAC.h"
#include "GPIO.h"
#include "bits.h"
#include "PIT.h"
#include "Signal_Generator.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (.0015738F)

void SM_SG_init(void);

void SM_SG_wave_creation(void);

void SM_on(void);

void SM_off(void);

void SM_PIT0_handler (void);


#endif /* SM_SG_H_ */
