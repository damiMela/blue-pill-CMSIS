/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/InputPin.h>
//#include <HAL/OutputPin.h>

InputPin::InputPin(uint8_t port, uint8_t pin, Mode mode) : Pin(port, pin) {
	_mode = mode;
}

void InputPin::init(void){
	GPIO_setDir(_port, _pin, INPUT);
	GPIO_setInputMode(_port, _pin, _mode);
}

//OutputPin InputPin::toOutputPin(OutputPin::Mode mode) {
//	return OutputPin(_port, _pin, mode);
//}
