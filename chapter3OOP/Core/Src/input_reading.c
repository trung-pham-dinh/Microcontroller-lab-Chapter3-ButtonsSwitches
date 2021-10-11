/*
 * input_reading.c
 *
 *  Created on: Oct 5, 2021
 *      Author: fhdtr
 */
#include "input_reading.h"

#define BUTTON_RELEASED GPIO_PIN_SET
#define BUTTON_PRESSED 	GPIO_PIN_RESET

unsigned int NO_OF_BUTTONS;
const uint16_t* buttonPort;

// the buffer that the final result is stored after debouncing
static GPIO_PinState* buttonBuffer;
// we define two buffers for debouncing
static GPIO_PinState* debounceButtonBuffer1;
static GPIO_PinState* debounceButtonBuffer2;


/**
  * @brief  Initialize for button reading.
  *
  * @note   None
  *
  * @param  port: Array of GPIO port for buttons
  * @param  no_buttons: number of buttons
  * @retval None
  */
void init_button_reading(const uint16_t* port, unsigned int no_buttons) {
	NO_OF_BUTTONS = no_buttons;

	buttonPort = port; // take array from user

	buttonBuffer = (GPIO_PinState*)malloc(NO_OF_BUTTONS*sizeof(GPIO_PinState));
	debounceButtonBuffer1 = (GPIO_PinState*)malloc(NO_OF_BUTTONS*sizeof(GPIO_PinState));
	debounceButtonBuffer2 = (GPIO_PinState*)malloc(NO_OF_BUTTONS*sizeof(GPIO_PinState));

	for(int i = 0; i < NO_OF_BUTTONS; i++) {
		buttonBuffer[i] = BUTTON_RELEASED;
		debounceButtonBuffer1[i] = BUTTON_RELEASED;
		debounceButtonBuffer2[i] = BUTTON_RELEASED;
	}
}


/**
  * @brief  Read the current state of button, then compare with the previous state to debounce.
  * 		The valid state will be store in a buffer
  * @note   None
  *
  * @param  None
  * @retval None
  */
void button_reading(void) {
	for(uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_PORT, buttonPort[i]);
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
			buttonBuffer[i] = debounceButtonBuffer1[i];
		}
	}
}


/**
  * @brief  check if button is currently pressed
  * @note   None
  *
  * @param  index: the index of button which we want to check
  * @retval output is 1 if the button is pressed, otherwise 0
  */
unsigned char is_button_pressed(uint8_t index) {
	if(index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_PRESSED);
}

