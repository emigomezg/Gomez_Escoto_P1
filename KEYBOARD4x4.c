/*
 * KEYBOARD4x4.c
 *
 *  Created on: Oct 3, 2019
 *      Author: alvar
 */

#include "KEYBOARD4x4.h"

volatile uint8_t g_port = 0;
volatile uint8_t g_data_available = 0;
volatile uint8_t g_data = 0;
volatile uint8_t g_pin_dataA = 0;
volatile uint8_t g_pin_dataB = 0;
volatile uint8_t g_pin_dataC = 0;
volatile uint8_t g_pin_dataD = 0;
volatile uint8_t g_pin_interrupt = 0;

uint8_t KEYBOARD_get_port(void) {
	return g_port;
}

void KEYBOARD_set_port(uint8_t port) {
	g_port = port;

}
uint32_t KEABOARD_decode_data(uint32_t data_in) {

	data_in &= (1 << g_pin_dataA | 1 << g_pin_dataB | 1 << g_pin_dataC
			| 1 << g_pin_dataD | 1 << g_pin_interrupt);
	switch (data_in) {
	case KEY_1:
		data_in = 1;
		break;
	case KEY_2:
		data_in = 2;
		break;
	case KEY_3:
		data_in = 3;
		break;
	case KEY_4:
		data_in = 4;
		break;
	case KEY_5:
		data_in = 5;
		break;
	case KEY_6:
		data_in = 6;
		break;
	case KEY_7:
		data_in = 7;
		break;
	case KEY_8:
		data_in = 8;
		break;
	case KEY_9:
		data_in = 9;
		break;
	case KEY_0:
		data_in = 0;
		break;
	case KEY_A:
		data_in = 0x0A;
		break;
	case KEY_B:
		data_in = 0x0B;
		break;
	case KEY_C:
		data_in = 0x0C;
		break;
	case KEY_D:
		data_in = 0x0D;
		break;
	case KEY_HASH:
		data_in = 0x0E;
		break;
	case KEY_ptr:
		data_in = 0x0F;
	default:
		data_in = 0x10;
		break;
	}
	return data_in;
}

void KEYBOARD_isr(void) {
	if (!g_data_available) {
		uint8_t gpio_port = KEYBOARD_get_port();
		volatile uint32_t data_in = GPIO_read_port(gpio_port);
		data_in = KEABOARD_decode_data(data_in);
		if (data_in != 0x10) {
			g_data = (uint8_t) data_in;
			g_data_available = TRUE;
		}
	}
}

void KEYBOARD_init(uint8_t gpio_port, uint8_t data1_pin, uint8_t data2_pin,
		uint8_t data3_pin, uint8_t data4_pin, uint8_t interrupt_pin) {
	g_pin_dataA = data1_pin;
	g_pin_dataB = data2_pin;
	g_pin_dataC = data3_pin;
	g_pin_dataD = data4_pin;
	g_pin_interrupt = interrupt_pin;
//local variables

	gpio_pin_control_register_t data_pins_cr = GPIO_MUX1 | GPIO_PS | GPIO_PE;
	gpio_pin_control_register_t interrupt_pin_cr = GPIO_MUX1 | GPIO_PS | GPIO_PE
			| INTR_FALLING_EDGE;

	GPIO_clock_gating(gpio_port);
	GPIO_pin_control_register(gpio_port, data1_pin, &data_pins_cr);
	GPIO_pin_control_register(gpio_port, data2_pin, &data_pins_cr);
	GPIO_pin_control_register(gpio_port, data3_pin, &data_pins_cr);
	GPIO_pin_control_register(gpio_port, data4_pin, &data_pins_cr);
	GPIO_pin_control_register(gpio_port, interrupt_pin, &interrupt_pin_cr);
	GPIO_data_direction_pin(gpio_port, GPIO_INPUT, data1_pin);
	GPIO_data_direction_pin(gpio_port, GPIO_INPUT, data2_pin);
	GPIO_data_direction_pin(gpio_port, GPIO_INPUT, data3_pin);
	GPIO_data_direction_pin(gpio_port, GPIO_INPUT, data4_pin);
	GPIO_data_direction_pin(gpio_port, GPIO_INPUT, interrupt_pin);
	KEYBOARD_set_port(gpio_port);

	GPIO_callback_init(KEYBOARD_isr, gpio_port);
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ, PRIORITY_0);
	NVIC_global_enable_interrupts;

}
uint8_t KEYBOARD_is_data_ready(void) {
	if (g_data_available) {
		return TRUE;
	} else {
		return FALSE;
	}
}
uint8_t KEYBOARD_get_data(void) {
	return g_data;
}
void KEYBOARD_clear_data_ready_flag(void) {
	g_data_available = FALSE;
}
