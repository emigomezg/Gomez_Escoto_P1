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


LED_config_t led_error = {GPIO_C,bit_17};
LED_config_t led_correct = {GPIO_B,bit_9};
uint8_t g_error_flag = FALSE, g_correct_flag=FALSE;
void PASSCNTL_PIT_handler(void);

void PASSCNTL_begin(void) {
	led_motor_pins_t LED1_motor={GPIO_C,bit_11};
	led_motor_pins_t LED2_motor={GPIO_C,bit_10};

	motor_pins_t MOTOR={GPIO_C,bit_16};

	KEYBOARD_init(KEYBOARD_PORT, KEYBOARD_DATA0, KEYBOARD_DATA1, KEYBOARD_DATA2,
	KEYBOARD_DATA3, KEYBOARD_DATA_READY_PIN); //
	//running necessary configuration in order to use the RGB in the k64

	MOTOR_begin(LED1_motor,LED2_motor,MOTOR);
	SM_LED_config_t sm_led1 ={GPIO_B,bit_18};
	SM_LED_config_t sm_led2 ={GPIO_B,bit_19};


	SM_SG_init(sm_led1,sm_led2);
	//GPIO_Error and pass
	gpio_pin_control_register_t pcr = GPIO_MUX1;

	GPIO_clock_gating(led_error.port);
	GPIO_clock_gating(led_correct.port);

	GPIO_pin_control_register(led_error.port, led_error.pin, &pcr);
	GPIO_pin_control_register(led_correct.port, led_correct.pin, &pcr);

	GPIO_clear_pin(led_error.port, led_error.pin);
	GPIO_clear_pin(led_correct.port, led_correct.pin);

	GPIO_data_direction_pin(led_correct.port, GPIO_OUTPUT, led_correct.pin);
	GPIO_data_direction_pin(led_error.port, GPIO_OUTPUT, led_error.pin);


	//PIT 2
	PIT_clock_gating();
	PIT_enable();
	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;
	My_float_pit_t onesec = 1.0;
	PIT_delay(PIT_2, SYSTEM_CLOCK, onesec);
	PIT_enable_interrupt(PIT_2);
	PIT_enable_timer(PIT_2);

	PIT_callback_init(PASSCNTL_PIT_handler, PIT_2);
	PIT_disable_timer(PIT_2);
}
void PASSCNTL_PIT_handler(void){
	static uint8_t times =4;
	if(g_error_flag){
		GPIO_toogle_pin(led_error.port, led_error.pin);
	}else if(g_correct_flag){
		GPIO_toogle_pin(led_correct.port, led_correct.pin);
	}
	times--;
	if(times==0){
			times=4;
			PIT_disable_timer(PIT_2);
			GPIO_clear_pin(led_error.port, led_error.pin);
			GPIO_clear_pin(led_correct.port, led_correct.pin);
			g_error_flag=FALSE;
			g_correct_flag=FALSE;
		}
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
					g_correct_flag=TRUE;
					PIT_enable_timer(PIT_2);
				}else{
					g_error_flag=TRUE;
					PIT_enable_timer(PIT_2);
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
				SM_off();
				MOTOR_off();
				machine_state_s.current_state= machine_state_s.next_state;
				update_state=FALSE;
				break;
			case STATE1:
				SM_off();
				MOTOR_on();
				machine_state_s.current_state= machine_state_s.next_state;
				update_state=FALSE;
				break;
			case STATE2:
				machine_state_s.current_state= machine_state_s.next_state;
				SM_on();
				MOTOR_off();
				update_state=FALSE;
				break;
			case STATE3:
				machine_state_s.current_state= machine_state_s.next_state;
				SM_on();
				MOTOR_on();
				update_state=FALSE;
				break;
			}


		}


	}
}
