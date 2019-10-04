/*
 * KEYBOARD4x4.h
 *
 *  Created on: Oct 3, 2019
 *      Author: alvar
 */

#ifndef KEYBOARD4X4_H_
#define KEYBOARD4X4_H_

#include "GPIO.h"



#define GPIO_CLOCKA  GPIO_CLOCK_GATING_PORTA
#define GPIO_CLOCKB  GPIO_CLOCK_GATING_PORTB
#define GPIO_CLOCKC  GPIO_CLOCK_GATING_PORTC
#define GPIO_CLOCKD  GPIO_CLOCK_GATING_PORTD
#define GPIO_CLOCKE  GPIO_CLOCK_GATING_PORTE

#define KEY_1 		3084
#define KEY_2 		3080
#define KEY_3 		3076
#define KEY_A 		3072
#define KEY_4 		2060
#define KEY_5 		2056
#define KEY_6 		2052
#define KEY_B 		2048
#define KEY_7		1036
#define KEY_8 		1032
#define KEY_9 		1028
#define KEY_C		1024
#define KEY_0 		8
#define KEY_HASH 	4
#define KEY_ptr	    12
#define KEY_D		0



void KEYBOARD_init(uint8_t GPIO_PORT,uint8_t data1_pin, uint8_t data2_pin, uint8_t data3_pin, uint8_t data4_pin,uint8_t interrupt_pin);




#endif /* KEYBOARD4X4_H_ */
