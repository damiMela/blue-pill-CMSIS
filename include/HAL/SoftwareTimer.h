/*
 * SoftwareTimer.h
 *
 *  Created on: 5 ene. 2021
 *      Author: usuario
 */
#ifndef DR_H_HAL_SOFTWARETIMER_H_
#define DR_H_HAL_SOFTWARETIMER_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <HAL/RHAL.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/
#define N_TIMERS	32
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

class SoftwareTimer{
public:
	SoftwareTimer(uint16_t time, void (*function)(void));
	void loop(void);
	bool pause(bool state);
	bool stop();
	int16_t get();
	bool set(uint16_t time);
	
	//void Close();
	static void tick(void);

//	friend void RHAL::tick(void (* func )(void));

private:
	uint8_t _index;
	uint16_t _time;
	void (*_function)(void);

	static uint16_t _timerCounters[ N_TIMERS ];
	static void (*_timerFunctions[ N_TIMERS ])(void);
	static uint32_t _runningTimers;
	static uint32_t _usedTimers;


protected:


};

#endif /* DR_H_HAL_SOFTWARETIMER_H_ */
