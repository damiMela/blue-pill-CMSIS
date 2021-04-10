/*
 * SW_Timer.h
 *
 *  Created on: 5 ene. 2021
 *      Author: usuario
 */
#define SW_TIMER_BEING_USED

#ifndef DR_H_HAL_SW_TIMER_H_
#define DR_H_HAL_SW_TIMER_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <HAL/RHAL.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/
#define N_TIMERS	32
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

class SW_Timer{
public:
	SW_Timer(uint16_t t, void (* f_event )(void));
	bool Pause(bool state);
	bool Stop();
	int16_t Get();
	bool Set(uint16_t t);
	void Close();
	static void Run(void);

//	friend void RHAL::do_every_1ms(void (* func )(void));

private:
	uint8_t _event_N;

	static uint16_t SW_TmrTime[ N_TIMERS ];
	static void (*SW_TmrFunc[ N_TIMERS ])(void);
	static uint32_t SW_TmrPlay;
	static uint32_t SW_TmrUsed;


protected:


};

#endif /* DR_H_HAL_SW_TIMER_H_ */
