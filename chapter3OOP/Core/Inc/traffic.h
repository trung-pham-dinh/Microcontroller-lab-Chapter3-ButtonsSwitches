/*
 * traffic.h
 *
 *  Created on: Oct 6, 2021
 *      Author: fhdtr
 */

#ifndef INC_TRAFFIC_H_
#define INC_TRAFFIC_H_

#include "main.h"
#include <stdlib.h>
#include "timer.h"
#include "functionality.h"

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

void init_traffic(const uint16_t* port, uint8_t* time, uint8_t* timeUpdate);
void traffic_display(void);
void clearTraffic(void);
uint8_t getUpdateFlag(void);
void updateNextPeriod(void);

#endif /* INC_TRAFFIC_H_ */
