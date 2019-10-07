/**
 \file	SM_SG
 \brief
This file contains the main implementatio of the signal generator, including 
state machine and initialization. 
 \author Emiliano Gómez Guerrero, IE708504@iteso.mx
 \date	4/10/2019
 \todo
 */

#ifndef SM_SG_H_
#define SM_SG_H_

#include "PIT.h"
#include "NVIC.h"
#include "MK64F12.h"
#include "DAC.h"
#include "GPIO.h"
#include "bits.h"
#include "PIT.h"
#include "Signal_Generator.h"
#include "RGBK64.h"

typedef struct {
	uint8_t port;
	uint8_t pin;
}SM_LED_config_t;

#define SYSTEM_CLOCK (21000000U)
#define DELAY (.0015738F) /*defined desired period for the PIT to generate a 5Hz signal
with 256 points per period*/

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function initialize the GPIO for the LEDs (external and RGB LEDs) and switches as 
 well as the PIT and NVIC for the waves.
 \param[in] structs with the port and pin for each LED used.
 \return void
 \todo 
 */
void SM_SG_init(SM_LED_config_t led1,SM_LED_config_t led2);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function contains the state machine for the wave generator.
 \param[in] void
 \return void
 \todo 
 */
void SM_SG_wave_creation(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function turns the global machine state flag on and enables the PIT.
 \param[in] void
 \return void
 \todo 
 */
void SM_on(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function turns the global machine state flag off disables the PIT as well as the 
 	external LEDs and internal RGB LEDs.
 \param[in] void
 \return void
 \todo 
 */
void SM_off(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function contains the ISR handler to be called.
 \param[in] void
 \return void
 \todo 
 */
void SM_PIT0_handler (void);


#endif /* SM_SG_H_ */
