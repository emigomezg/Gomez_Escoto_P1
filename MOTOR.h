/*
 * MOTOR.h
 *
 *  Created on: Oct 6, 2019
 *      Author: alvar
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "GPIO.h"
#include "PIT.h"
#include "NVIC.h"

typedef struct{
	uint8_t port;
	uint8_t pin;
}led_motor_pins_t;

typedef struct{
	uint8_t port;
	uint8_t pin;
}motor_pins_t;


void MOTOR_begin(led_motor_pins_t led1,led_motor_pins_t led2,motor_pins_t motor);

#endif /* MOTOR_H_ */
