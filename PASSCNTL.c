/*
 * PASSCNTL.c
 *
 *  Created on: Oct 4, 2019
 *      Author: alvaro
 */

#include "PASSCNTL.h"

#define KEYBOARD_PORT			GPIO_B
#define KEYBOARD_DATA0 			bit_11
#define KEYBOARD_DATA1 			bit_10
#define KEYBOARD_DATA2 			bit_3
#define KEYBOARD_DATA3			bit_2
#define KEYBOARD_DATA_READY_PIN bit_20




#define PASS_SIZE 4

#define AS 0x0A
#define BS 0x0B

enum {
	STATE0, STATE1, STATE2, STATE3
} states;

typedef struct {
	uint8_t port;
	uint8_t pin;
	gpio_pin_control_register_t pcr;
	uint8_t direction;
} LED_config_t;

struct MACHINE {
	uint8_t current_state;
	uint8_t next_state;
} machine_state_s;

const uint8_t g_masterpass[4] = { 1, 2, 3, 4 };
const uint8_t g_signal_pass[4] = { 4, 5, 6, 7 };
const uint8_t g_motor_pass[4] = { 7, 8, 9, 0 };

volatile uint8_t g_state_machine_status = FALSE;
volatile uint8_t g_passcode[4] = { 0 };
volatile uint8_t g_pass_index = 0;


volatile uint8_t update_state = FALSE;
volatile uint8_t A_selected_flag = FALSE;
volatile uint8_t B_selected_flag = FALSE;
volatile uint8_t control_machine = 0;


void PASSCNTL_begin(void) {
	led_motor_pins_t LED1_motor={GPIO_C,bit_11};
	led_motor_pins_t LED2_motor={GPIO_C,bit_10};

	motor_pins_t MOTOR={GPIO_C,bit_16};

	KEYBOARD_init(KEYBOARD_PORT, KEYBOARD_DATA0, KEYBOARD_DATA1, KEYBOARD_DATA2,
	KEYBOARD_DATA3, KEYBOARD_DATA_READY_PIN); //
	//running necessary configuration in order to use the RGB in the k64
	RGB_Begin();
	MOTOR_begin(LED1_motor,LED2_motor,MOTOR);
	SM_SG_init();
}
void PSSCNTL_clean_passcode(void) {
	g_pass_index = 0;
	for (int a = 4; a > 0; a--) {
		g_passcode[a - 1] = 0;
	}

}
void PASSCNTL_master_passcode(void) {
	volatile uint8_t temp_data = 0;
	while (g_state_machine_status == FALSE) {
		if (KEYBOARD_is_data_ready()) {
			temp_data = KEYBOARD_get_data();
			KEYBOARD_clear_data_ready_flag();
			if ((temp_data != BS) && (temp_data != AS)
					&& (temp_data != 0x10)) {
				g_passcode[g_pass_index] = temp_data;
				g_pass_index++;
			}
			if (g_pass_index == PASS_SIZE) {
				for (int a = 0; a < PASS_SIZE; a++) {
					if (g_passcode[a] == g_masterpass[a])
						g_pass_index--;
				}
				if (g_pass_index == 0) {
					g_state_machine_status = TRUE;
				}
				g_pass_index = 0;
			}
		}
	}
	machine_state_s.current_state = STATE0;
	machine_state_s.next_state = STATE1;
}
void PASSCNTL_verfiy_state(uint8_t temp_data,uint8_t possible1,uint8_t possible2) {
	if ((temp_data == AS) && (A_selected_flag == FALSE)) {
		A_selected_flag = TRUE;
		g_pass_index=0;
		control_machine = temp_data;
	} else if ((temp_data == BS) && (B_selected_flag == FALSE)) {
		B_selected_flag = TRUE;
		g_pass_index=0;
		control_machine = temp_data;
	} else if ((control_machine)
			&& ((temp_data != AS) && (temp_data != BS))) {
		g_passcode[g_pass_index] = temp_data;
		g_pass_index++;
	}else{
		A_selected_flag=FALSE;
		B_selected_flag=FALSE;
	}
	if (g_pass_index == PASS_SIZE && control_machine == AS) {
		for (int a = 0; a < PASS_SIZE; a++) {
			if (g_passcode[a] == g_signal_pass[a])
				g_pass_index--;
		}
		if (g_pass_index == 0) {
			update_state = TRUE;
			machine_state_s.next_state = possible1;
		}
		g_pass_index = 0;
	} else if (g_pass_index == PASS_SIZE && control_machine == BS) {
		for (int a = 0; a < PASS_SIZE; a++) {
			if (g_passcode[a] == g_motor_pass[a])
				g_pass_index--;
		}
		if (g_pass_index == 0) {
			update_state = TRUE;
			machine_state_s.next_state = possible2;
			control_machine=0;
			A_selected_flag=FALSE;
			B_selected_flag=FALSE;
		}else{
			//error on
		}
		control_machine=0;
		g_pass_index = 0;
	}
}

void PASSCNTL_loop(void) {
	PASSCNTL_master_passcode();
	uint8_t temp_data = 0;

	for (;;) {
		if (KEYBOARD_is_data_ready()) {
			temp_data = KEYBOARD_get_data();
			KEYBOARD_clear_data_ready_flag();
			switch (machine_state_s.current_state) {
			case STATE0:
				PASSCNTL_verfiy_state(temp_data,STATE1,STATE2);
				break;
			case STATE1:
				PASSCNTL_verfiy_state(temp_data,STATE0,STATE3);
				break;
			case STATE2:
				PASSCNTL_verfiy_state(temp_data,STATE3,STATE0);
				break;
			case STATE3:
				PASSCNTL_verfiy_state(temp_data,STATE2,STATE1);
				break;
			}
		}
		if(update_state){
			switch(machine_state_s.next_state){
			case STATE0:
				//SM_off();
				//SM_mot_off();
				machine_state_s.current_state= machine_state_s.next_state;
				update_state=FALSE;
				break;
			case STATE1:
				//SM_off();
				//SM_mot_on();
				machine_state_s.current_state= machine_state_s.next_state;
				update_state=FALSE;
				break;
			case STATE2:
				machine_state_s.current_state= machine_state_s.next_state;
				//SM_on();
				//SM_mot_off();
				update_state=FALSE;
				break;
			case STATE3:
				machine_state_s.current_state= machine_state_s.next_state;
				//SM_on();
				//SM_mot_on();
				update_state=FALSE;
				break;
			}


		}


	}
}
