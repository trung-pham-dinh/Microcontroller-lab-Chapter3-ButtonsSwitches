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
	STATE_RED,
	STATE_GREEN,
	STATE_YELLOW,
	STATE_WAIT,
} TrafficState;

static TrafficState ver_state, hor_state;

static const uint16_t* lightPort;
static uint8_t* lightTime;

static uint16_t allpin;
static uint8_t readyForNewPeriod = 1;
static uint8_t periodDone = 0;

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

			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_RED], LIGHT_SET);
		break;
	case STATE_GREEN:
		if(getSecFlag(TRAFFIC_VER_TIMER)) {
			setSecTimer(TRAFFIC_VER_TIMER, lightTime[VER_YELLOW]);
			ver_state = STATE_YELLOW;

			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_GREEN], LIGHT_SET);
		break;
	case STATE_YELLOW:
		if(getSecFlag(TRAFFIC_VER_TIMER)) {
			ver_state = STATE_WAIT;

			readyForNewPeriod = 0;
			periodDone = 1;
			clearTraffic();
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_YELLOW], LIGHT_SET);
		break;
	case STATE_WAIT:
		if(readyForNewPeriod) {
			periodDone = 0;
			ver_state = STATE_RED;
			setSecTimer(TRAFFIC_VER_TIMER, lightTime[VER_RED]);
		}
		break;
	}



	switch(hor_state) {
	case STATE_GREEN:
		if(getSecFlag(TRAFFIC_HOR_TIMER)) {
			setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_YELLOW]);
			hor_state = STATE_YELLOW;

			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_GREEN], LIGHT_SET);
		break;
	case STATE_YELLOW:
		if(getSecFlag(TRAFFIC_HOR_TIMER)) {
			setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_RED]);
			hor_state = STATE_RED;

			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_YELLOW], LIGHT_SET);
		break;
	case STATE_RED:
		if(getSecFlag(TRAFFIC_HOR_TIMER)) {
			hor_state = STATE_WAIT;

			readyForNewPeriod = 0;
			periodDone = 1;
			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_RED], LIGHT_SET);
		break;
	case STATE_WAIT:
		if(readyForNewPeriod) {
			periodDone = 0;
			hor_state = STATE_GREEN;
			setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_GREEN]);
		}
		break;
	}

}

void clearTraffic(void) {
	HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_YELLOW], LIGHT_RESET);
	HAL_GPIO_WritePin(TRAFFIC_PORT, allpin, LIGHT_RESET);
}

uint8_t isPeriodDone(void) {
	return periodDone;
}
void startNewPeriod(void) {
	readyForNewPeriod = 1;
}
