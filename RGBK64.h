/*
 * RGBK64.h
 *
 *  Created on: Sep 9, 2019
 *      Author: alvaro
 */

#ifndef RGBK64_H_
#define RGBK64_H_

#include <bits.h>
#include "MK64F12.h"
#include "stdint.h"
#include "GPIO.h"


typedef enum {
	RGB_RED, RGB_GREEN, RGB_BLUE, RGB_CYAN, RGB_PURPLE, RGB_YELLOW, RGB_WHITE
} rgb_color_t;

//Starts Corresponding Peripheral ports, sets PIN as GPIO, SET RGB ON OFF STATE, SETS PINS AS OUTPUTS
void RGB_Begin(void);
//displays the color selected
void RGB_Set_Color(uint8_t color);
//removes certain color without affecting the other colors already on
void RGB_Clear_Color(uint8_t color);

#endif /* RGBK64_H_ */
