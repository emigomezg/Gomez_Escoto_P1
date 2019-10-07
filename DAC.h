/**
 \file	DAC
 \brief
 This is the source file for the DAC device driver for Kinetis K64.
 It contains all the implementation for configuration functions and runtime functions.
 i.e., this is the application programming interface (API) for the DAC peripheral.
 \author Emiliano Gómez Guerrero, IE708504@iteso.mx
 \date	4/10/2019
 \todo
 Interrupts are not implemented in this API implementation.
 */

#ifndef DAC_H_
#define DAC_H_

#include "MK64F12.h"

typedef struct  {
	uint8_t data_high;
	uint8_t data_low;
}dac_data_out_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function initialize the DAC0 (clock gating and enable).
 \param[in] void
 \return void
 \todo 
 */
void DAC0_init(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function sets a specific value in the DAC0[0] (not using buffer) register.
 \param[in]  struct type with 2 inner uint8_t numbers as low and high part.
 \return void
 \todo Buffer implementation. 
 */
void DAC0_out_value(dac_data_out_t);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function initialize the DAC1 (clock gating and enable).
 \param[in] void
 \return void
 \todo 
 */
void DAC1_init(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function sets a specific value in the DAC1[0] (not using buffer) register.
 \param[in]  struct type with 2 inner uint8_t numbers as low and high part.
 \return void
 \todo Buffer implementation. 
 */
void DAC1_out_value(dac_data_out_t);

#endif /* DAC_H_ */
