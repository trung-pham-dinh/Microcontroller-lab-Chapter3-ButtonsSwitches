/*
 * traffic.c
 *
 *  Created on: Oct 6, 2021
 *      Author: fhdtr
 */

#include "traffic.h"

#define LIGHT_SET 		GPIO_PIN_RESET
#define LIGHT_RESET 	GPIO_PIN_SET

typedef enum {
	VER_RED,
	VER_GREEN,
	VER_YELLOW,
	HOR_RED,
	HOR_GREEN,
	HOR_YELLOW

} TrafficArrayAccess;

typedef enum {
	TRAFFIC_VER_TIMER,
	TRAFFIC_HOR_TIMER
} TimerSecArrayAccess;

typedef enum {
	STATE_RED,
	STATE_GREEN,
	STATE_YELLOW,
} TrafficState;

static TrafficState ver_state, hor_state;

static const uint16_t* lightPort;
static uint8_t* lightTime;

static uint16_t allpin;

void init_traffic(const uint16_t* port, uint8_t* time) {
	lightPort = port;
	lightTime = time;

	ver_state = STATE_YELLOW;
	hor_state = STATE_RED;

	allpin = lightPort[0] | lightPort[1] | lightPort[2] | lightPort[3] | lightPort[4] | lightPort[5];
	HAL_GPIO_WritePin(TRAFFIC_PORT, allpin, LIGHT_RESET);
}

void traffic_display(void) {
	switch(ver_state) {
	case STATE_RED:
		if(getSecFlag(TRAFFIC_VER_TIMER)) {
			setSecTimer(TRAFFIC_VER_TIMER, lightTime[VER_GREEN]);
			ver_state = STATE_GREEN;

			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_RED], LIGHT_RESET);
			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_GREEN], LIGHT_SET);
		}
		break;
	case STATE_GREEN:
		if(getSecFlag(TRAFFIC_VER_TIMER)) {
			setSecTimer(TRAFFIC_VER_TIMER, lightTime[VER_YELLOW]);
			ver_state = STATE_YELLOW;

			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_GREEN], LIGHT_RESET);
			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_YELLOW], LIGHT_SET);
		}
		break;
	case STATE_YELLOW:
		if(getSecFlag(TRAFFIC_VER_TIMER)) {
			setSecTimer(TRAFFIC_VER_TIMER, lightTime[VER_RED]);
			ver_state = STATE_RED;

			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_YELLOW], LIGHT_RESET);
			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_RED], LIGHT_SET);
		}
		break;
	}



	switch(hor_state) {
	case STATE_GREEN:
		if(getSecFlag(TRAFFIC_HOR_TIMER)) {
			setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_YELLOW]);
			hor_state = STATE_YELLOW;

			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_GREEN], LIGHT_RESET);
			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_YELLOW], LIGHT_SET);
		}
		break;
	case STATE_YELLOW:
		if(getSecFlag(TRAFFIC_HOR_TIMER)) {
			setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_RED]);
			hor_state = STATE_RED;

			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_YELLOW], LIGHT_RESET);
			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_RED], LIGHT_SET);
		}
		break;
	case STATE_RED:
		if(getSecFlag(TRAFFIC_HOR_TIMER)) {
			setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_GREEN]);
			hor_state = STATE_GREEN;

			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_RED], LIGHT_RESET);
			HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_GREEN], LIGHT_SET);
		}
		break;
	}
}
