/*
 * main.c
 *
 *  Created on: Oct 2, 2019
 *      Author: emi_g
 */
#include "Signal_Generator.h"

int main(void)
{
	DAC0_init();

	for(;;)
	{
		DAC0_signal_creator(SINE);
	}
    return 0 ;
}
