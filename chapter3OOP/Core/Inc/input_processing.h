/*
 * input_processing.h
 *
 *  Created on: Oct 5, 2021
 *      Author: fhdtr
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "main.h"
#include <stdlib.h>

#include "timer.h"
#include "led7_display.h"
#include "traffic.h"
#include "functionality.h"

typedef enum {
	BUTTON_MODE,
	BUTTON_FUNC
} ButtonArrayAccess;

void init_fsm_input_processing(TIM_HandleTypeDef* htim);
void fsm_for_input_processing(void);
void fsm_for_traffic_control(void);
void setBufferLed7(uint8_t firstPair, uint8_t secondPair);
void process(ButtonArrayAccess button);
void scanLed7();
void increase(uint8_t* buffer);
void decrease(uint8_t* buffer);
void blinkTraffic(void);
#endif /* INC_INPUT_PROCESSING_H_ */
