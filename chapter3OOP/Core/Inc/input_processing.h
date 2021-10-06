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
#include "input_reading.h"

void init_fsm_input_processing(const uint16_t* port, unsigned int no_buttons);
void fsm_for_input_processing(void);
uint8_t getPressFlag(unsigned int index);
void resetPressFlag(unsigned int index);

#endif /* INC_INPUT_PROCESSING_H_ */
