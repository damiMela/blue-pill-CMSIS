/*
 * Pin.cpp
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/Pin.h>
#include <Hardware/DR_GPIO.h>

Pin::Pin(uint8_t port, uint8_t pin) {
	_pin = pin;
	_port = port;
}
