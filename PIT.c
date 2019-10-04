/**
	\file
	\brief
		This is the source file for the PIT device driver for Kinetis K64.
		It contains some configuration functions and runtime functions.
		It is implemented using  CMSIS Core functions
	\author Emiliano Gomez
	\date	17/09/2019

 */

#include "PIT.h"

static pit_interrupt_flags_t g_pit_flag = {0};

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay)
{
	uint32_t LDVAL = 0;
	My_float_pit_t pit_clock = system_clock/2;
	My_float_pit_t pit_clock_period = (1/pit_clock);
	LDVAL = (uint32_t)(delay/pit_clock_period);
	LDVAL -= 1;

	PIT->CHANNEL[pit_timer].LDVAL = LDVAL;
}

void PIT_enable(void)
{
	PIT->MCR &= ~(PIT_MCR_MDIS_MASK);
	PIT->MCR |= PIT_MCR_FRZ_MASK;
}

void PIT_clock_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

void PIT_enable_interrupt(PIT_timer_t pit)
{
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK;
}

void PIT_enable_timer (PIT_timer_t pit)
{
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void PIT_clear_interrupt_flag(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
			g_pit_flag.pit_flag_0 = FALSE;
		break;

		case PIT_1:
			g_pit_flag.pit_flag_1 = FALSE;
		break;

		case PIT_2:
			g_pit_flag.pit_flag_2 = FALSE;
		break;

		case PIT_3:
			g_pit_flag.pit_flag_3 = FALSE;
		break;

		default:
			g_pit_flag.pit_flag_0 = FALSE;
			g_pit_flag.pit_flag_1 = FALSE;
			g_pit_flag.pit_flag_2 = FALSE;
			g_pit_flag.pit_flag_3 = FALSE;
		break;
	}
}

uint8_t PIT_get_interrupt_flag_status(PIT_timer_t pit)
{
	uint8_t state;
	state = 0;

	switch(pit)
	{
		case PIT_0:
			state = g_pit_flag.pit_flag_0;
		break;

		case PIT_1:
			state = g_pit_flag.pit_flag_1;
		break;

		case PIT_2:
			state = g_pit_flag.pit_flag_2;
		break;

		case PIT_3:
			state = g_pit_flag.pit_flag_3;
		break;

		default:
		break;
	}
	return state;
}

void PIT0_IRQHandler(void)
{
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	uint32_t dummyRead =  PIT->CHANNEL[0].TCTRL;
	g_pit_flag.pit_flag_0 = TRUE;
}

void PIT1_IRQHandler(void)
{
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	uint32_t dummyRead =  PIT->CHANNEL[1].TCTRL;
	g_pit_flag.pit_flag_1 = TRUE;
}

void PIT2_IRQHandler(void)
{
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
	uint32_t dummyRead =  PIT->CHANNEL[2].TCTRL;
	g_pit_flag.pit_flag_2 = TRUE;
}

void PIT3_IRQHandler(void)
{
	PIT->CHANNEL[3].TFLG |= PIT_TFLG_TIF_MASK;
	uint32_t dummyRead =  PIT->CHANNEL[3].TCTRL;
	g_pit_flag.pit_flag_3 = TRUE;
}

