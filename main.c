/*
 * main.c
 *
 *  Created on: Oct 2, 2019
 *      Author: emi_g
 */
#include "Signal_Generator.h"
#include "SM_SG.h"

int main(void)
{
	SM_SG_init();
	SM_on();
	for(;;)
	{}
    return 0 ;
}
