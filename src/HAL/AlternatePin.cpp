/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/AlternatePin.h>

void AlternatePin::paramInit(uint8_t port, uint8_t pin, Mode mode, uint8_t maxVel){
	GPIO_setDir(port, pin, ALTERNATE);
	GPIO_setAltMode(port, pin, mode);
	GPIO_setMaxOutputSpeed(port, pin, maxVel);
}