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

bool& operator << (bool &val, const InputPin &i_pin) {
	val = GPIO_getPin(i_pin._port, i_pin._pin);
	return val;
}

OutputPin& operator << (OutputPin &o_pin, const InputPin &i_pin){
	o_pin.set(GPIO_getPin(i_pin._port, i_pin._pin));
	return o_pin;
}