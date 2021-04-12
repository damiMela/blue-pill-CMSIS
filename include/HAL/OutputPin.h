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

class OutputPin : Pin {

public:
	enum Mode {PUSH_PULL, OPEN_DRAIN};
	OutputPin(uint8_t port, uint8_t pin, Mode mode = Mode::PUSH_PULL);
	void init(void);
	inline void set(bool v){	GPIO_setPin(_port, _pin, v);	};
	inline void operator <<(bool v) {	GPIO_setPin(_port, _pin, v);	};
	
	friend bool& operator<< (bool &val, const OutputPin &o_pin);
	OutputPin operator<< (OutputPin &o_pin_s){
		GPIO_setPin(this->_port, 
		this->_pin,
		GPIO_getStatus(o_pin_s._port, o_pin_s._pin));
		return *this;
	}


private:
	uint8_t _mode;
};

#endif /* DR_H_HAL_OUTPUTPIN_H_ */
