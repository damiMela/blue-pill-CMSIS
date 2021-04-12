/*
 * RHAL.h
 *
 *  Created on: Jan 6, 2021
 *      Author: Damián
 */

#ifndef DR_H_HAL_RHAL_H_
#define DR_H_HAL_RHAL_H_

#include <System.h>

//Hal includes
#include <HAL/SW_Timer.h>
#include <HAL/OutputPin.h>
#include <HAL/InputPin.h>
#include <HAL/AlternativePin.h>

class RHAL{
public:
	RHAL();
	void tick(void (* func )(void));

private:
	void _initClock();
	inline uint8_t _systick(){
		uint8_t res = main_flags.Systick_ms;
		main_flags.Systick_ms = 0;
		return res;
	};
};




#endif /* DR_H_HAL_RHAL_H_ */
