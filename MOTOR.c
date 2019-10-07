/*
 * MOTOR.c
 *
 *  Created on: Oct 6, 2019
 *      Author: alvar
 */

#include "MOTOR.h"
#define DELAY1 (2.0F)
#define DELAY2 (6.0F)
#define DELAY3 (8.0F)

#define SYSTEM_CLOCK (21000000U)
#define delay_state (.01F)
typedef enum {
	PSTATE0, PSTATE1, PSTATE2, PSTATE3
} pit_state_t;
typedef enum{
	LED_OFF,LED_ON
}leds;

typedef struct
{
	My_float_pit_t time[4];
	uint8_t num_states;
	uint8_t index;
	uint8_t led1_status;
	uint8_t led2_status;
} pit_state_machine_t;

struct motor
{
	uint8_t port;
	uint8_t pin;
}g_motor,g_led1,g_led2;
uint8_t current_state = PSTATE0;

pit_state_machine_t state[3];

volatile uint8_t g_motor_global_state = 0;

void MOTOR_PIT1_handler(void);
void MOTOR_GPIOC_handler(void);

void MOTOR_begin(led_motor_pins_t led1, led_motor_pins_t led2,motor_pins_t motor)
{
	state[0].led1_status =LED_OFF;
	state[0].led2_status =LED_OFF;
	state[1].time[0] = DELAY1;
	state[1].time[1] = DELAY1;
	state[1].time[2] = DELAY2;
	state[1].time[3] = DELAY1;
	state[1].index = 0;
	state[1].num_states = 4;
	state[1].led1_status = LED_ON;
	state[1].led2_status = LED_OFF;
	state[2].time[0] = DELAY3;
	state[2].time[1] = DELAY3;
	state[2].index = 0;
	state[2].num_states = 2;
	state[2].led1_status = LED_OFF;
	state[2].led2_status = LED_ON;


	g_motor.port = motor.port;
	g_motor.pin = motor.pin;
	g_led1.pin = led1.pin;
	g_led1.port = led1.port;
	g_led2.port = led2.port;
	g_led2.pin = led2.pin;

	gpio_pin_control_register_t led_motor_pcr = (GPIO_MUX1);

	//clock gating GPIO_ports
	GPIO_clock_gating(led1.port);
	GPIO_clock_gating(led2.port);
	GPIO_clock_gating(motor.port);

	//necessary configuration for led and motor
	GPIO_pin_control_register(led1.port, led1.pin, &led_motor_pcr);
	GPIO_pin_control_register(led2.port, led2.pin, &led_motor_pcr);
	GPIO_pin_control_register(motor.port, motor.pin, &led_motor_pcr);

	//setting a safe value for output pins
	GPIO_clear_pin(led1.port, led1.pin);
	GPIO_clear_pin(led2.port, led2.pin);
	GPIO_clear_pin(motor.port, motor.pin);

	//setting pins directions
	GPIO_data_direction_pin(led1.port, GPIO_OUTPUT, led1.pin);
	GPIO_data_direction_pin(led2.port, GPIO_OUTPUT, led2.pin);
	GPIO_data_direction_pin(motor.port, GPIO_OUTPUT, motor.pin);

	GPIO_sw2_begin(INTERRUPT);

	PIT_clock_gating();
	PIT_enable();
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_2);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;

	PIT_delay(PIT_1, SYSTEM_CLOCK, delay_state);
	PIT_enable_interrupt(PIT_1);
	PIT_enable_timer(PIT_1);

	PIT_callback_init(MOTOR_PIT1_handler, PIT_1);
	GPIO_callback_init(MOTOR_GPIOC_handler, GPIO_C);
	PIT_disable_timer(PIT_1);

}
void MOTOR_PIT1_handler(void)
{
	if (g_motor_global_state)
	{
		if (current_state != PSTATE0)
		{
			GPIO_toogle_pin(g_motor.port, g_motor.pin);
			state[current_state].index++;
			if (state[current_state].index == state[current_state].num_states)
				state[current_state].index = 0;
			PIT_delay(PIT_1, SYSTEM_CLOCK,
			state[current_state].time[state[current_state].index]);

		} else
		{
			GPIO_clear_pin(g_motor.port, g_motor.pin);
		}
	}
	PIT_clear_interrupt_flag(PIT_1);

}
void MOTOR_GPIOC_handler(void)
{
	if (g_motor_global_state)
	{
		current_state++;
		if (current_state == PSTATE3)
			current_state = PSTATE0;
		if(current_state==PSTATE0)
		{
			PIT_disable_timer(PIT_1);
			GPIO_clear_pin(g_motor.port, g_motor.pin);
		}else
			PIT_enable_timer(PIT_1);
		if(state[current_state].led1_status)
			GPIO_set_pin(g_led1.port, g_led1.pin);
		else
			GPIO_clear_pin(g_led1.port, g_led1.pin);
		if(state[current_state].led2_status)
			GPIO_set_pin(g_led2.port, g_led2.pin);
		else
		{
			GPIO_clear_pin(g_led2.port, g_led2.pin);
		}

		state[current_state].index=0;

	}
}

void MOTOR_on()
{
	g_motor_global_state = TRUE;
	PIT_enable_timer(PIT_1);
}
void MOTOR_off()
{
	g_motor_global_state = FALSE;
	GPIO_clear_pin(g_led1.port, g_led1.pin);
	GPIO_clear_pin(g_led2.port, g_led2.pin);
	GPIO_clear_pin(g_motor.port, g_motor.pin);
	PIT_disable_timer(PIT_1);
}
