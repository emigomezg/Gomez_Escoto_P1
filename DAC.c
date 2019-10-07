/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

#include "DAC.h"

void DAC0_init(void)
{
    SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;   /* clock to DAC module */
    DAC0->C0 |= 0xC0;                    /* enable DAC and use software trigger */
}

void DAC1_init(void)
{
    SIM->SCGC2 |= SIM_SCGC2_DAC1_MASK;   /* clock to DAC module */
    DAC1->C0 |= 0xC0;                    /* enable DAC and use software trigger */
}

void DAC0_out_value(dac_data_out_t data_out)
{

	DAC0->DAT[0].DATL = data_out.data_low;	
	DAC0->DAT[0].DATH = data_out.data_high;
}

void DAC1_out_value(dac_data_out_t data_out)
{

	DAC1->DAT[0].DATL = data_out.data_low;
	DAC1->DAT[0].DATH = data_out.data_high;
}
