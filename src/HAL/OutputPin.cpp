/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/OutputPin.h>
//#include <DR_h/HAL/InputPin.h>


OutputPin::OutputPin(uint8_t port, uint8_t pin, Mode mode) : Pin(port, pin) {
	_mode = mode;
}

void OutputPin::init(void){
	GPIO_setDir(_port, _pin, OUTPUT);
	GPIO_setOutputMode(_port, _pin, _mode);
}

//InputPin OutputPin::toInputPin(InputPin::Mode mode) {
//	return InputPin(_port, _pin, mode);
//}
