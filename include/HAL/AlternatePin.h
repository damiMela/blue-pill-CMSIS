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
#include <Hardware/DR_GPIO.h>

class AlternatePin : Pin {

public:
	enum Mode {PUSH_PULL = 2, OPEN_DRAIN};
	static void paramInit(uint8_t port, uint8_t pin, Mode mode, uint8_t maxVel = MAX_VEL_10MHZ);

private:
};

#endif /* DR_H_HAL_ALTERNATEPIN_H_ */
