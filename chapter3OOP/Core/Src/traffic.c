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
	STATE_UPDATE,
} TrafficState;

// fsm state for display traffic lights(vertical road and horizontal road)
static TrafficState ver_state, hor_state;

// provided by user: Array of port for traffic lights
static const uint16_t* lightPort;

// provided by user: Array of time value for each traffic light
static uint8_t* lightTime;
static uint8_t* lightTimeUpdate;


static uint16_t allpin; // represent for all traffic lights pin
static uint8_t isUpdate = 0;


/**
  * @brief  Initialize traffic lights.
  *
  * @note   Array length must be 6
  *
  * @param  port: Array of GPIO port for traffic lights
  * @param  time: Array of time value for each traffic light
  * @retval None
  */
void init_traffic(const uint16_t* port, uint8_t* time, uint8_t* timeUpdate) {
	lightPort = port;
	lightTime = time;
	lightTimeUpdate = timeUpdate;

	ver_state = STATE_YELLOW;
	hor_state = STATE_RED;

	allpin = lightPort[0] | lightPort[1] | lightPort[2] | lightPort[3] | lightPort[4] | lightPort[5];
	HAL_GPIO_WritePin(TRAFFIC_PORT, allpin, LIGHT_RESET);
}


/**
  * @brief  A FSM for display traffic lights corresponding to its lighting time.
  *
  * @note   This function need timer.h to function
  *
  * @param  None
  * @retval None
  */
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
			ver_state = STATE_UPDATE;

			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[VER_YELLOW], LIGHT_SET);
		break;
	case STATE_UPDATE:
		if(getUpdateFlag()) {
			copyArray(lightTimeUpdate, lightTime, 6);
		}
		setSecTimer(TRAFFIC_VER_TIMER, lightTime[VER_RED]);
		ver_state = STATE_RED;
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
			hor_state = STATE_UPDATE;

			clearTraffic();
			break;
		}
		HAL_GPIO_WritePin(TRAFFIC_PORT, lightPort[HOR_RED], LIGHT_SET);
		break;
	case STATE_UPDATE:
		if(getUpdateFlag()) {
			copyArray(lightTimeUpdate, lightTime, 6);
		}
		setSecTimer(TRAFFIC_HOR_TIMER, lightTime[HOR_GREEN]);
		hor_state = STATE_GREEN;
		break;
	}

}


/**
  * @brief  Turn off all traffic lights.
  *
  * @note   None
  *
  * @param  None
  * @retval None
  */
void clearTraffic(void) {
	HAL_GPIO_WritePin(TRAFFIC_PORT, allpin, LIGHT_RESET);
}

/**
  * @brief  check if the display is done its period.
  *
  * @note   the flag is clear by "void traffic_display(void)"
  *
  * @param  None
  * @retval A flag to indicate the period is done
  */
uint8_t getUpdateFlag(void) {
	if(isUpdate) {
		isUpdate = 0;
		return 1;
	}
	return 0;
}
void updateNextPeriod(void) {
	isUpdate = 1;
}
