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

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function initialize the GPIO used for the motor and the motor LEDs. 
 \param[in] struct cointaning the the bit as well as the port thats going to be used. 
 \return void
 \todo 
 */
void MOTOR_begin(led_motor_pins_t led1,led_motor_pins_t led2,motor_pins_t motor);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function turns the motor flag on and initialize the PIT for the desired turned on time.
 \param[in] void
 \return void
 \todo 
 */
void MOTOR_on(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	  This function turns the motor flag off, turns the motor off and also the LEDs. PIT timer 
 	  is also disable.
 \param[in] struct cointaning the the bit as well as the port thats going to be used. 
 \return void
 \todo 
 */
void MOTOR_off(void);

#endif /* MOTOR_H_ */
