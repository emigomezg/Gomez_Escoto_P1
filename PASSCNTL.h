/**
 \file	PASSCNTL
 \brief
This file coontains the main functions of the system as well as the 
initialization of it. 
 \author Alvaro Escoto Ramirez, ie717487@iteso.mx
 \date	4/10/2019
 \todo
 */

#ifndef PASSCNTL_H_
#define PASSCNTL_H_


#include "KEYBOARD4x4.h"
#include "RGBK64.h"
#include "GPIO.h"
#include "SM_SG.h"
#include "MOTOR.h"
#include "bits.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function contains the general state machine of the system and moves between those
 states.
 \param[in] void
 \return void
 \todo 
 */
void PASSCNTL_loop(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function contains initialization of almost the whole system: keyboard, LEDs, 
         motor pin, NVIC and PIT.
         
 \param[in] void
 \return void
 \todo 
 */
void PASSCNTL_begin(void);


#endif /* PASSCNTL_H_ */
