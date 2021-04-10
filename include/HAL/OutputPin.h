/*
 * OutputPin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#ifndef DR_H_HAL_OUTPUTPIN_H_
#define DR_H_HAL_OUTPUTPIN_H_

#include "System.h"
#include <HAL/Pin.h>
#include <Hardware/DR_GPIO.h>
//#include "InputPin.h"

class OutputPin : Pin {

public:
	enum Mode {PUSH_PULL, OPEN_DRAIN};
	OutputPin(uint8_t port, uint8_t pin, Mode mode = Mode::PUSH_PULL);
	inline void set(bool v){	GPIO_setPin(_port, _pin, v);	};
	inline void operator=(bool v) {	GPIO_setPin(_port, _pin, v);	};
//	InputPin toInputPin(InputPin::Mode mode);

};

#endif /* DR_H_HAL_OUTPUTPIN_H_ */