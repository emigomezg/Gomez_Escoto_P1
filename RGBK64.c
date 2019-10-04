/*
 * RGBK64.c
 *
 *  Created on: Sep 9, 2019
 *      Author: alvar
 */


#include "RGBK64.h"

void RGB_Begin(void) {
	gpio_pin_control_register_t rgb_pcr_config = GPIO_MUX1;
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_E);
	GPIO_pin_control_register(GPIO_B, bit_21, &rgb_pcr_config);
	GPIO_pin_control_register(GPIO_B, bit_22, &rgb_pcr_config);
	GPIO_pin_control_register(GPIO_E, bit_26, &rgb_pcr_config);
	GPIO_set_pin(GPIO_B, bit_21);
	GPIO_set_pin(GPIO_B, bit_22);
	GPIO_set_pin(GPIO_E, bit_26);
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21);
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22);
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26);
}
void RGB_Set_Color(uint8_t color) {
	switch (color) {
	case RGB_RED:
		GPIO_clear_pin(GPIO_B, bit_22);
		break;
	case RGB_GREEN:
		GPIO_clear_pin(GPIO_E, bit_26);
		break;
	case RGB_BLUE:
		GPIO_clear_pin(GPIO_B, bit_21);
		break;
	case RGB_CYAN:
		GPIO_clear_pin(GPIO_B, bit_21);
		GPIO_clear_pin(GPIO_E, bit_26);
		break;
	case RGB_PURPLE:
		GPIO_clear_pin(GPIO_B, bit_21);
		GPIO_clear_pin(GPIO_B, bit_22);
		break;
	case RGB_YELLOW:
		GPIO_clear_pin(GPIO_B, bit_22);
		GPIO_clear_pin(GPIO_E, bit_26);
		break;
	case RGB_WHITE:
		GPIO_clear_pin(GPIO_B, bit_21);
		GPIO_clear_pin(GPIO_B, bit_22);
		GPIO_clear_pin(GPIO_E, bit_26);
	default:
		break;
	}

}
void RGB_Clear_Color(uint8_t color) {
	switch (color) {
	case RGB_RED:
		GPIO_set_pin(GPIO_B, bit_22);
		break;
	case RGB_GREEN:
		GPIO_set_pin(GPIO_E, bit_26);
		break;
	case RGB_BLUE:
		GPIO_set_pin(GPIO_B, bit_21);
		break;
	case RGB_CYAN:
		GPIO_set_pin(GPIO_B, bit_21);
		GPIO_set_pin(GPIO_E, bit_26);
		break;
	case RGB_PURPLE:
		GPIO_set_pin(GPIO_B, bit_21);
		GPIO_set_pin(GPIO_B, bit_22);
		break;
	case RGB_YELLOW:
		GPIO_set_pin(GPIO_B, bit_22);
		GPIO_set_pin(GPIO_E, bit_26);
		break;
	case RGB_WHITE:
		GPIO_set_pin(GPIO_B, bit_21);
		GPIO_set_pin(GPIO_B, bit_22);
		GPIO_set_pin(GPIO_E, bit_26);
	default:
		break;
	}
}


