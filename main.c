/**
 * @file    Practica1.c
 * @brief   Application entry point.
*/
#include "MK64F12.h"
/* TODO: insert other include files here. */


#include "PASSCNTL.h"

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {


	PASSCNTL_begin();
  	/* Init board hardware. */
	while(1){
		PASSCNTL_loop();
	}


    return 0 ;
}
