/*
 * MOTOR.c
 *
 *  Created on: Oct 6, 2019
 *      Author: alvar
 */

#include "MOTOR.h"
#define DELAY1 (1.0F)
#define DELAY2 (3.0F)
#define DELAY3 (4.0F)

#define SYSTEM_CLOCK (21000000U)
#define delay_state (.01F)
typedef enum{
	PSTATE0,PSTATE1,PSTATE2,PSTATE3
};

typedef struct{
	uint8_t current_state;
	My_float_pit_t time[4];
	uint8_t num_states;
}pit_state_machine_t;

pit_state_machine_t state1={PSTATE0,{DELAY1,DELAY1,DELAY2,DELAY1},4};
pit_state_machine_t state2={PSTATE1,{DELAY3,DELAY3},2};

volatile uint8_t g_motor_global_state = 0;

void MOTOR_begin(led_motor_pins_t led1, led_motor_pins_t led2,
		motor_pins_t motor)
{

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
	GPIO_data_direction_pin(led1.port, OUTPUT, led1.pin);
	GPIO_data_direction_pin(led2.port, OUTPUT, led2.pin);
	GPIO_data_direction_pin(led1.port, OUTPUT, led1.pin);
	GPIO_data_direction_pin(led2.port, OUTPUT, led2.pin);

	GPIO_sw2_begin(INTERRUPT);

	PIT_clock_gating();
	PIT_enable();
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_2);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;
	PIT_delay(PIT_1, SYSTEM_CLOCK, delay_state);

	//PIT_callback_init(SM_PIT0_handler, PIT_1);
	//GPIO_callback_init(SM_SG_wave_creation, GPIO_C);

}
void MOTOR_PIT1_handler(void)
{

}
void MOTOR_GPIOC_handler(void)
{
	if(g_motor_global_state){
		switch(motor_state_machine.current)
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
	PIT_disable_timer(PIT_1);
}
