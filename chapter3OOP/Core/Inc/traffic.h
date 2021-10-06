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

void init_traffic(const uint16_t* port, uint8_t* time);
void traffic_display(void);

#endif /* INC_TRAFFIC_H_ */
