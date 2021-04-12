/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#ifndef DR_H_HAL_PIN_H_
#define DR_H_HAL_PIN_H_

#include <System.h>

class Pin {

public:
	Pin(uint8_t port, uint8_t pin);
	virtual void init() = 0;

protected:
	uint8_t _port;
	uint8_t _pin;

};

#endif
