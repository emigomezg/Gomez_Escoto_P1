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
SM_LED_config_t g_smled1,g_smled2;

void SM_SG_init(SM_LED_config_t led1,SM_LED_config_t led2)
{
	g_smled1.port = led1.port;
	g_smled1.pin = led1.pin;

	g_smled2.port = led2.port;
	g_smled2.pin = led2.pin;
	gpio_pin_control_register_t pcr = (GPIO_MUX1);
	GPIO_clock_gating(led1.port);
	GPIO_clock_gating(led2.port);

	GPIO_pin_control_register(led1.port, led1.pin, &pcr);
	GPIO_pin_control_register(led2.port, led2.pin, &pcr);

	GPIO_clear_pin(led1.port, led1.pin);
	GPIO_clear_pin(led2.port, led2.pin);

	GPIO_data_direction_pin(led1.port, GPIO_OUTPUT, led1.pin);
	GPIO_data_direction_pin(led2.port, GPIO_OUTPUT, led2.pin);




	GPIO_sw3_begin(INTERRUPT);

	PIT_clock_gating();
	PIT_enable();
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_2);

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;

	PIT_delay(PIT_0, SYSTEM_CLOCK, delay_state);
	PIT_enable_interrupt(PIT_0);

	DAC0_init();
	RGB_Begin();

	PIT_callback_init(SM_PIT0_handler,PIT_0);

	GPIO_callback_init(SM_SG_wave_creation,GPIO_A);
}


void SM_SG_wave_creation(void)
{
	if(g_machine_state == TRUE)
	{
		RGB_Clear_Color(RGB_WHITE);
		switch(g_waveform)
		{
		case NONE:
			g_waveform = SQUARE;
			RGB_Set_Color(RGB_BLUE);
			GPIO_set_pin(g_smled1.port, g_smled1.pin);
			GPIO_clear_pin(g_smled2.port, g_smled2.pin);
		break;
		case SQUARE:
			g_waveform = SINE;
			RGB_Set_Color(RGB_RED);
			GPIO_clear_pin(g_smled1.port, g_smled1.pin);
			GPIO_set_pin(g_smled2.port, g_smled2.pin);
		break;
		case SINE:
			RGB_Set_Color(RGB_GREEN);
			g_waveform = TRIANGLE;
			GPIO_clear_pin(g_smled1.port, g_smled1.pin);
			GPIO_clear_pin(g_smled2.port, g_smled2.pin);
		break;
		case TRIANGLE:
			g_waveform = NONE;
			GPIO_clear_pin(g_smled1.port, g_smled1.pin);
			GPIO_clear_pin(g_smled2.port, g_smled2.pin);
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
	GPIO_clear_pin(g_smled1.port, g_smled1.pin);
	GPIO_clear_pin(g_smled2.port, g_smled2.pin);
	RGB_Clear_Color(RGB_WHITE);
}

void SM_PIT0_handler (void)
{
	DAC0_signal_creator(g_waveform);
}
