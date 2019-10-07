/*
 * KEYBOARD4x4.h
 *
 *  Created on: Oct 3, 2019
 *      Author: alvar
 */

#ifndef KEYBOARD4X4_H_
#define KEYBOARD4X4_H_

#include "GPIO.h"
#include "NVIC.h"
#include "bits.h"


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

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function initializes the desired port and bits(4 data bits and 1 interrupt bit)
         to be used with matrix keyboard (4*4) 
 \param[in]  The desired port, 4 bits for data and 1  bit for the interrupt. 
 \return void
 \todo 
 */
void KEYBOARD_init(uint8_t GPIO_PORT,uint8_t data1_pin, uint8_t data2_pin, 
                   uint8_t data3_pin, uint8_t data4_pin,uint8_t interrupt_pin);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function checks if there is any data available to be acquire by using a global flag.
 \param[in]  void
 \return void
 \todo 
 */
uint8_t KEYBOARD_is_data_ready(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function clears the global variable that checks if there is any data available to
         be colected.
 \param[in]  void
 \return void
 \todo 
 */
void KEYBOARD_clear_data_ready_flag(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function gets the data global variable and returns it when called.
 \param[in]  void
 \return uint8_t
 \todo 
 */
uint8_t KEYBOARD_get_data(void);


#endif /* KEYBOARD4X4_H_ */
