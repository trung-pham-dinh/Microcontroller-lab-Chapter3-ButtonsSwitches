/*
 * functionality.c
 *
 *  Created on: Oct 24, 2021
 *      Author: fhdtr
 */

#include "functionality.h"

void copyArray(uint8_t* from, uint8_t* to, int n) {
	for(int i = 0; i < n; i++) {
		to[i] = from[i];
	}
}
