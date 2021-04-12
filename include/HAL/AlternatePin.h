/*
 * AlternatePin.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ianicknoejovich
 */

#ifndef DR_H_HAL_ALTERNATEPIN_H_
#define DR_H_HAL_ALTERNATEPIN_H_

#include <System.h>
#include <HAL/Pin.h>

class AlternatePin : Pin {

public:
	enum Mode {PUSH_PULL, OPEN_DRAIN};
	AlternatePin(uint8_t port, uint8_t pin, Mode mode);
	void init(void);

private:
	Mode _mode;
};

#endif /* DR_H_HAL_ALTERNATEPIN_H_ */
