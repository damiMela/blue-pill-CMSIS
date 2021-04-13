/*
 * HardwareTimer.h
 *
 *  Created on: 5 ene. 2021
 *      Author: Damian Melamed
 */
#ifndef DR_H_HAL_HARDWARETIMER_H_
#define DR_H_HAL_HARDWARETIMER_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <HAL/RHAL.h>

#include <Hardware/DR_Timer.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/

/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

class HardwareTimer{
public:
	HardwareTimer(uint8_t timer, uint16_t presc, uint16_t val, void (*function)(void));
	void start(void);
	void reset(void);
	bool pause(bool state);
	bool stop();
	int16_t get();
	bool set(uint16_t time);
	
	//void Close();
	static void tick(void);

//	friend void RHAL::tick(void (* func )(void));

private:
    uint8_t _timerN;
	uint16_t _presc;
	uint16_t _val;

protected:


};

#endif /* DR_H_HAL_SOFTWARETIMER_H_ */
