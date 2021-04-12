/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/AlternatePin.h>
#include <Hardware/DR_GPIO.h>

AlternatePin::AlternatePin(uint8_t port, uint8_t pin, Mode mode) : Pin(port, pin) {
	_mode = mode;
}

void AlternatePin::init() {
	GPIO_setDir(_port, _pin, ALTERNATE);
	GPIO_setAltMode(_port, _pin, ALTERNATE_PUSHPULL);
}
