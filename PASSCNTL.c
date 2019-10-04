/*
 * PASSCNTL.c
 *
 *  Created on: Oct 4, 2019
 *      Author: alvar
 */

#include "PASSCNTL.h"

#define KEYBOARD_PORT			GPIO_B
#define KEYBOARD_DATA0 			bit_11
#define KEYBOARD_DATA1 			bit_10
#define KEYBOARD_DATA2 			bit_3
#define KEYBOARD_DATA3			bit_2
#define KEYBOARD_DATA_READY_PIN bit_20

typedef struct {
	uint8_t port;
	uint8_t pin;
	gpio_pin_control_register_t pcr;
	uint8_t direction;
} LED_config_t;

void PASSCNTL_begin(void) {

	LED_config_t LED_inicio = { GPIO_A, bit_0, GPIO_MUX1, OUTPUT };
	LED_config_t LED_error = { GPIO_A, bit_0, GPIO_MUX1, OUTPUT };
	LED_config_t LED_motor1 = { GPIO_A, bit_0, GPIO_MUX1, OUTPUT };
	LED_config_t LED_motor2 = { GPIO_A, bit_0, GPIO_MUX1, OUTPUT };
	LED_config_t LED_gen1 = { GPIO_A, bit_0, GPIO_MUX1, OUTPUT };
	LED_config_t LED_gen2 = { GPIO_A, bit_0, GPIO_MUX1, OUTPUT };

	KEYBOARD_init(KEYBOARD_PORT, KEYBOARD_DATA0, KEYBOARD_DATA1, KEYBOARD_DATA2,
			KEYBOARD_DATA3, KEYBOARD_DATA_READY_PIN); //
	//running necesary configuration in order to use the RGB in the k64
	RGB_Begin();

	//clcock_gating_necesesary LEDS
	GPIO_clock_gating(LED_inicio.port);
	GPIO_clock_gating(LED_error.port);
	GPIO_clock_gating(LED_motor1.port);
	GPIO_clock_gating(LED_motor2.port);
	GPIO_clock_gating(LED_gen1.port);
	GPIO_clock_gating(LED_gen2.port);

	//PCR_LEDS;
	GPIO_pin_control_register(LED_inicio.port, LED_inicio.pin, &LED_inicio.pcr);
	GPIO_pin_control_register(LED_error.port, LED_error.pin, &LED_error.pcr);
	GPIO_pin_control_register(LED_motor1.port, LED_motor1.pin, &LED_motor1.pcr);
	GPIO_pin_control_register(LED_motor2.port, LED_motor2.pin, &LED_motor2.pcr);
	GPIO_pin_control_register(LED_gen1.port, LED_gen1.pin, &LED_gen1.pcr);
	GPIO_pin_control_register(LED_gen2.port, LED_gen2.pin, &LED_gen2.pcr);

	//LED PORTS SET AS OUTPUT
	GPIO_data_direction_pin(LED_inicio.port, LED_inicio.direction,
			LED_inicio.pin);
	GPIO_data_direction_pin(LED_error.port, LED_error.direction, LED_error.pin);
	GPIO_data_direction_pin(LED_motor1.port, LED_motor1.direction,
			LED_motor1.pin);
	GPIO_data_direction_pin(LED_motor2.port, LED_motor2.direction,
			LED_motor2.pin);
	GPIO_data_direction_pin(LED_gen1.port, LED_gen1.direction, LED_gen1.pin);
	GPIO_data_direction_pin(LED_gen2.port, LED_gen2.direction, LED_gen2.pin);
	//necesarry config for use of switches as interruptions on raising edge interrupt
	GPIO_sw2_begin(INTERRUPT);
	GPIO_sw3_begin(INTERRUPT);
}
