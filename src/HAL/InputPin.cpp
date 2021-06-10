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
	
	if(_mode == PULLDOWN) GPIO_setInputMode(_port, _pin, _mode-1);
	else GPIO_setInputMode(_port, _pin, _mode);

	if(_mode == PULLUP) GPIO_setPull(_port, _pin, HIGH);
	else GPIO_setPull(_port, _pin, LOW);
	
}
