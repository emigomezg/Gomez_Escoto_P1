/*
 * PIT_SG.c
 *
 *  Created on: Oct 4, 2019
 *      Author: emi_g
 */

#include "PIT_SG.h"
#include "PIT.h"
#include "NVIC.h"
#include "MK64F12.h"
#include "DAC.h"
#include "GPIO.h"
#include "bits.h"
#include "PIT.h"
#include "Signal_Generator.h"

My_float_pit_t delay_state = DELAY;
uint8_t pit_inter_status = FALSE;

void PIT_SG_init(void)
{
	gpio_pin_control_register_t pin_control_register_bit_sw = GPIO_MUX1|GPIO_PS|GPIO_PE|INTR_FALLING_EDGE;

	GPIO_clock_gating(GPIO_A);

	GPIO_pin_control_register(GPIO_A, bit_4, &pin_control_register_bit_sw);
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, bit_4);

	PIT_clock_gating();
	PIT_enable();
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_2);

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;

	PIT_delay(PIT_0, SYSTEM_CLOCK, delay_state);
	PIT_enable_timer(PIT_0);

	PIT_enable_interrupt(PIT_0);

	DAC0_init();
}


void PIT_SG_loop(void)
{
	waveform_t waveform = TRIANGLE;
	for(;;){
		if(TRUE == GPIO_get_irq_status(GPIO_C))
				{
					switch(waveform)
					{
					case TRIANGLE:
						waveform = SINE;
					break;
					case SINE:
						waveform = TRIANGLE;
					break;
					default:
						waveform = TRIANGLE;
					break;
					}
					DAC0_signal_creator(waveform);
					GPIO_clear_irq_status(GPIO_C);
				}
				do
				{
					pit_inter_status =  PIT_get_interrupt_flag_status(PIT_0);
				}
				while(FALSE == pit_inter_status);

				GPIO_toogle_pin(GPIO_D, bit_0);

				PIT_clear_interrupt_flag(PIT_0);
		}

}
