/*
 * Pin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#include <HAL/InputPin.h>
//#include <DR_h/HAL/OutputPin.h>
#include <Hardware/DR_GPIO.h>

InputPin::InputPin(uint8_t port, uint8_t pin, Mode mode) : Pin(port, pin) {
	GPIO_portEn(_port);
	GPIO_setDir(_port, _pin, INPUT);
	GPIO_setInputMode(_port, _pin, mode);
}

inline bool InputPin::read() {
	return GPIO_getPin(_port, _pin);
}

inline bool InputPin::operator()() {
	return GPIO_getPin(_port, _pin);
}

//OutputPin InputPin::toOutputPin(OutputPin::Mode mode) {
//	return OutputPin(_port, _pin, mode);
//}
