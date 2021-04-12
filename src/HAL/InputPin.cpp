/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/InputPin.h>

InputPin::InputPin(uint8_t port, uint8_t pin, Mode mode) : Pin(port, pin) {
	_mode = mode;
}

void InputPin::init(void){
	GPIO_setDir(_port, _pin, INPUT);
	GPIO_setInputMode(_port, _pin, _mode);
}

/* bool operator << (bool val, InputPin &i_pin){
	val = i_pin.read();
	return val;
} */
