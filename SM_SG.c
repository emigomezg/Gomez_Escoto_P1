/*
 * PIT_SG.c
 *
 *  Created on: Oct 4, 2019
 *      Author: emi_g
 */

#include "SM_SG.h"


volatile uint8_t g_machine_state = FALSE;

volatile uint8_t g_waveform = NONE;

My_float_pit_t delay_state = DELAY;

void SM_SG_init(void)
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
	PIT_enable_interrupt(PIT_0);

	DAC0_init();

	PIT_callback_init(SM_PIT0_handler,PIT_0);

	GPIO_callback_init(SM_SG_wave_creation,GPIO_A);
}


void SM_SG_wave_creation(void)
{
	if(g_machine_state == TRUE)
	{
		switch(g_waveform)
		{
		case NONE:
			g_waveform = SQUARE;
		break;
		case SQUARE:
			g_waveform = SINE;
		break;
		case SINE:
			g_waveform = TRIANGLE;
		break;
		case TRIANGLE:
			g_waveform = NONE;
		break;
		default:
			g_waveform = NONE;
		break;
		}
	}
}


void SM_on(void)
{
	g_machine_state = TRUE;
	PIT_enable_timer(PIT_0);
}

void SM_off(void)
{
	g_machine_state = FALSE;
	PIT_disable_timer(PIT_0);
}

void SM_PIT0_handler (void)
{
	DAC0_signal_creator(g_waveform);
}
