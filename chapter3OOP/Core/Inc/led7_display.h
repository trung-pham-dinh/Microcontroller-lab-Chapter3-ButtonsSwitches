/*
 * led7_display.h
 *
 *  Created on: Oct 5, 2021
 *      Author: fhdtr
 */

#ifndef INC_LED7_DISPLAY_H_
#define INC_LED7_DISPLAY_H_

#include "main.h"
#include <stdlib.h>

void init_led7(const uint16_t* en, const uint16_t* port, uint8_t* buffer, unsigned int no_led7);
void display_7SEG(unsigned int index);

#endif /* INC_LED7_DISPLAY_H_ */
