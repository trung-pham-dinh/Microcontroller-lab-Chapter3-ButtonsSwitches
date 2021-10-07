/*
 * led7_display.c
 *
 *  Created on: Oct 5, 2021
 *      Author: fhdtr
 */

#include "led7_display.h"


static uint8_t seg7Hex[] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x04, 0xff}; // last one is for clear
static const GPIO_PinState ENABLE_LED = GPIO_PIN_RESET;
static const GPIO_PinState DISABLE_LED = GPIO_PIN_SET;
static const GPIO_PinState SET_SEG = GPIO_PIN_RESET;
static const GPIO_PinState RESET_SEG = GPIO_PIN_SET;

static unsigned int NO_OF_LED7;

static const uint16_t* seg7Port;
static const uint16_t* seg7En;

static uint8_t* seg7Val;
static uint16_t allseg;

void init_led7(const uint16_t* en, const uint16_t* port, uint8_t* buffer, unsigned int no_led7) {
	NO_OF_LED7 = no_led7;

	seg7En = en;
	seg7Port = port;
	seg7Val = buffer;
	allseg = seg7Port[0] | seg7Port[1] | seg7Port[2] | seg7Port[3] | seg7Port[4] | seg7Port[5] | seg7Port[6];
}

void display_7SEG(unsigned int index) {
	HAL_GPIO_WritePin(SEG_PORT, allseg, RESET_SEG);

	uint8_t hexcode = seg7Hex[seg7Val[index]];
	for(int i = 0; i < 7; i++) {
		if((hexcode & (0x40 >> i)) == 0)
			HAL_GPIO_WritePin(SEG_PORT, seg7Port[i], SET_SEG);
	}

	for(int i = 0;  i < NO_OF_LED7; i++) {
		if(i == index)
			HAL_GPIO_WritePin(SEG_PORT, seg7En[i], ENABLE_LED);
		else
			HAL_GPIO_WritePin(SEG_PORT, seg7En[i], DISABLE_LED);
	}
}
