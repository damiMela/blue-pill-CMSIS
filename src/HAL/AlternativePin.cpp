/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/AlternativePin.h>
#include <Hardware/DR_GPIO.h>

AlternativePin::AlternativePin(uint8_t port, uint8_t pin, Mode mode) : Pin(port, pin) {
	GPIO_portEn(_port);
	GPIO_setDir(_port, _pin, ALTERNATE);
	GPIO_setAltMode(_port, _pin, ALTERNATE_PUSHPULL);
}
