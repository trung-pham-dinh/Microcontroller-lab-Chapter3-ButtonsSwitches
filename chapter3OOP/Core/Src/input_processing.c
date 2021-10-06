/*
 * input_processing.c
 *
 *  Created on: Oct 5, 2021
 *      Author: fhdtr
 */
#include "input_processing.h"
typedef enum {
	STATE_RELEASED,
	STATE_PRESSED
} ButtonState;
ButtonState* buttonState;

static uint8_t* flagPressed;

void init_fsm_input_processing(const uint16_t* port, unsigned int no_buttons) {
	init_button_reading(port, no_buttons);

	buttonState = (ButtonState*)malloc(NO_OF_BUTTONS*sizeof(ButtonState));
	flagPressed = (uint8_t*)malloc(NO_OF_BUTTONS*sizeof(uint8_t));

	for(int i = 0; i < NO_OF_BUTTONS; i++) {
		 buttonState[i] = STATE_RELEASED;
		 flagPressed[i] = 0;
	}
}
void fsm_for_input_processing(void) {
	for(int i = 0; i < NO_OF_BUTTONS; i++) {
		switch(buttonState[i]) {
		case STATE_RELEASED:
			if(is_button_pressed(i)) {
				buttonState[i] = STATE_PRESSED;
			}
			break;
		case STATE_PRESSED:
			if(!is_button_pressed(i)) {
				buttonState[i] = STATE_RELEASED;
				flagPressed[i] = 1;
			}
			break;
		}
	}
}

uint8_t getPressFlag(unsigned int index) {
	return flagPressed[index];
}
void resetPressFlag(unsigned int index) {
	flagPressed[index] = 0;
}

