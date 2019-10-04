/**
 * @file    Practica1.c
 * @brief   Application entry point.
*/
#include "MK64F12.h"
/* TODO: insert other include files here. */


#include "KEYBOARD4x4.h"

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	KEYBOARD_init(GPIO_B,bit_11,bit_10,bit_3,bit_2,bit_20);

  	/* Init board hardware. */
	while(1){

	}


    return 0 ;
}
