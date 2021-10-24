/*
 * input_processing.c
 *
 *  Created on: Oct 5, 2021
 *      Author: fhdtr
 */
#include "input_processing.h"

// Timer parameter
typedef enum {
	SCAN_TIMER,
	BLINK_TIMER
} TimerMilArrayAccess;
const unsigned int NO_OF_MIL_TIMERS = 2;
const unsigned int NO_OF_SEC_TIMERS = 2;
const unsigned int scanTime = 250;
const unsigned int blinkTime = 500;

// LED parameter
#define NO_OF_LED7 		4

const uint16_t seg7_port[7] = {SEG_0, SEG_1, SEG_2, SEG_3, SEG_4, SEG_5, SEG_6};
const uint16_t seg7_en[NO_OF_LED7] = {EN_SEG_0, EN_SEG_1, EN_SEG_2, EN_SEG_3};
uint8_t buffer_led7[NO_OF_LED7] = {0,1,2,4};


// Button parameter
#define NO_OF_BUTTONS   2

typedef enum {
	STATE_RELEASED,
	STATE_PRESSED
} ButtonState;
ButtonState* buttonState;


const uint16_t button_port[NO_OF_BUTTONS] = {BUTTON_MODE_PORT, BUTTON_FUNC_PORT};

// Traffic parameter
typedef enum {
	NORMAL,
	PLUS_RED,
	PLUS_GREEN,
	PLUS_YELLOW,
	MINUS_RED,
	MINUS_GREEN,
	MINUS_YELLOW,
	CONFIRM,
} ModeState;
ModeState trafficMode = NORMAL;
const uint16_t traffic_port[6] = {RED_VER, GREEN_VER, YELLOW_VER, RED_HOR, GREEN_HOR, YELLOW_HOR};
uint8_t traffic_time[6] = {9,6,3,9,6,3};
uint8_t traffic_time_update[6] = {9,6,3,9,6,3};

/**
  * @brief  Initialize input processing
  * @note   None
  *
  * @param  port: Array of GPIO port for buttons
  * @param  no_buttons: Number of buttons
  * @retval None
  *
  */


void init_fsm_input_processing(TIM_HandleTypeDef* htim) {
	init_timer(htim, NO_OF_SEC_TIMERS, NO_OF_MIL_TIMERS);
	init_led7(seg7_en, seg7_port, buffer_led7, NO_OF_LED7);
	init_button_reading(button_port, NO_OF_BUTTONS);
	init_traffic(traffic_port, traffic_time, traffic_time_update);



	buttonState = (ButtonState*)malloc(NO_OF_BUTTONS*sizeof(ButtonState));

	for(int i = 0; i < NO_OF_BUTTONS; i++) {
		 buttonState[i] = STATE_RELEASED;
	}


}



/**
  * @brief 	To read a single click(press then release) of buttons
  * @note   None
  *
  * @param  None
  * @retval None
  */
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
				process(i);
			}
			break;
		}
	}
}

void fsm_for_traffic_control(void) {
	switch(trafficMode) {
	case NORMAL:
		traffic_display();
		setBufferLed7(getSecCounter(TRAFFIC_VER_TIMER), getSecCounter(TRAFFIC_HOR_TIMER));
		break;
	case PLUS_RED:
	case PLUS_GREEN:
	case PLUS_YELLOW:
		setBufferLed7(traffic_time_update[trafficMode-1], 2);
		blinkTraffic();
		break;
	case MINUS_RED:
	case MINUS_GREEN:
	case MINUS_YELLOW:
		setBufferLed7(traffic_time_update[trafficMode-4], 3);
		blinkTraffic();
		break;
	case CONFIRM:
		setBufferLed7(4, 4);
		blinkTraffic();
		break;
	}
	scanLed7();
}

void process(ButtonArrayAccess button) {
	static uint8_t updateFlag = 0;
	switch(button) {
	case BUTTON_MODE:
		switch(trafficMode) {
		case NORMAL:
			controlSecTimer(TRAFFIC_VER_TIMER, STOP_TIMER);
			controlSecTimer(TRAFFIC_HOR_TIMER, STOP_TIMER);
			break;
		case CONFIRM:
			if(updateFlag) {
				updateFlag = 0;
				updateNextPeriod();
			}
			else {
				copyArray(traffic_time, traffic_time_update, 6);
			}
			controlSecTimer(TRAFFIC_VER_TIMER, START_TIMER);
			controlSecTimer(TRAFFIC_HOR_TIMER, START_TIMER);
		default:
			break;
		}
		clearTraffic();
		trafficMode = (trafficMode != CONFIRM)? trafficMode+1 : NORMAL;
		break;
	case BUTTON_FUNC:
		switch(trafficMode) {
		case PLUS_RED:
		case PLUS_GREEN:
		case PLUS_YELLOW:
			increase(traffic_time_update);
			break;
		case MINUS_RED:
		case MINUS_GREEN:
		case MINUS_YELLOW:
			decrease(traffic_time_update);
			break;
		case CONFIRM:
			updateFlag = 1;
			break;
		default:
			break;
		}
		break;
	}
}


void setBufferLed7(uint8_t firstPair, uint8_t secondPair) {
	buffer_led7[0] = firstPair / 10;
	buffer_led7[1] = firstPair % 10;
	buffer_led7[2] = secondPair / 10;
	buffer_led7[3] = secondPair % 10;
}

void scanLed7() {
	static uint8_t index = 0;

	if(getMilFlag(SCAN_TIMER)) {
		setMilTimer(SCAN_TIMER, scanTime);
		display_7SEG(index++);
		if(index == 4) index = 0;
	}
}

//			RV          GV    YV
//	|-----------------|------|---|
//	|------------|----|----------|
//        GH       YH      RH
void increase(uint8_t* buffer) {
	switch(trafficMode) {
	case PLUS_RED:
		if(buffer[VER_GREEN]-1 > 0 && buffer[HOR_RED]-1 > 1) {
			buffer[VER_RED]++;
			buffer[VER_GREEN]--;

			buffer[HOR_RED]--;
			buffer[HOR_GREEN]++;
		}
		break;
	case PLUS_GREEN:
		if(buffer[VER_RED]-1 > 1 && buffer[HOR_GREEN]-1 > 0) {
			buffer[VER_GREEN]++;
			buffer[VER_RED]--;

			buffer[HOR_GREEN]--;
			buffer[HOR_RED]++;
		}
		break;
	case PLUS_YELLOW:
		if(buffer[VER_GREEN]-1 > 0) {
			buffer[VER_YELLOW]++;
			buffer[VER_GREEN]--;
		}
		break;
	default:
		break;
	}
}

void decrease(uint8_t* buffer) {
	switch(trafficMode) {
	case MINUS_RED:
		if(buffer[VER_RED]-1 > 1 && buffer[VER_GREEN]-1 > 0) {
			buffer[VER_RED]--;
			buffer[VER_GREEN]++;

			buffer[HOR_RED]++;
			buffer[HOR_GREEN]--;
		}
		break;
	case MINUS_GREEN:
		if(buffer[VER_GREEN]-1 > 0 && buffer[HOR_RED]-1 > 1) {
			buffer[VER_GREEN]--;
			buffer[VER_RED]++;

			buffer[HOR_GREEN]++;
			buffer[HOR_RED]--;
		}
		break;
	case MINUS_YELLOW:
		if(buffer[VER_YELLOW]-1 > 0) {
			buffer[VER_YELLOW]--;
			buffer[VER_GREEN]++;
		}
		break;
	default:
		break;
	}
}


void blinkTraffic() {
	if(trafficMode == NORMAL) return;

	if(getMilFlag(BLINK_TIMER)) {
		setMilTimer(BLINK_TIMER, blinkTime);
		if(trafficMode == PLUS_RED || trafficMode == MINUS_RED) {
			HAL_GPIO_TogglePin(TRAFFIC_PORT, RED_VER | RED_HOR);
		}
		else if(trafficMode == PLUS_GREEN || trafficMode == MINUS_GREEN) {
			HAL_GPIO_TogglePin(TRAFFIC_PORT, GREEN_VER | GREEN_HOR);
		}
		else if(trafficMode == PLUS_YELLOW || trafficMode == MINUS_YELLOW){
			HAL_GPIO_TogglePin(TRAFFIC_PORT, YELLOW_VER | YELLOW_HOR);
		}
		else if(trafficMode == CONFIRM){
			HAL_GPIO_TogglePin(TRAFFIC_PORT, YELLOW_VER | YELLOW_HOR | GREEN_VER | GREEN_HOR | RED_VER | RED_HOR);
		}
	}
}

