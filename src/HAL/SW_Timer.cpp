/*
 * SW_Timer.cpp
 *
 *  Created on: 5 ene. 2021
 *      Author: usuario
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <HAL/SW_Timer.h>

/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/
#define PauseTmr(b)		(SW_TmrPlay &= ~(1 << b))
#define StartTmr(b)		(SW_TmrPlay |= (1 << b))
#define TmrPlayState(b)	((SW_TmrPlay >> b) & 0x01)

#define setTmrUsed(b)	(SW_TmrUsed |= (1 << b))
#define clrTmrUsed(b)	(SW_TmrUsed &= ~(1 << b))
#define TmrUsedState(b)	((SW_TmrUsed >> b) & 0x01)
/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/
uint16_t SW_Timer::SW_TmrTime[ N_TIMERS ] = {0};
void (*SW_Timer::SW_TmrFunc[ N_TIMERS ])(void) = {nullptr};
uint32_t SW_Timer::SW_TmrUsed = 0;
uint32_t SW_Timer::SW_TmrPlay = 0;
/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

SW_Timer::SW_Timer(uint16_t t , void (* f_event )(void)){
	main_flags.SW_timer_used = 1;
	_TmrTime = t;
	_TmrFunc = f_event;

		for(uint8_t i = 0; i < N_TIMERS; i++){
		if(!TmrUsedState(i)) {
			_event_N = i;
			SW_TmrFunc[_event_N] = _TmrFunc;
			SW_TmrTime[_event_N] = _TmrTime;

			StartTmr(_event_N);
			setTmrUsed(_event_N);
			break;
		}
	}
}


void SW_Timer::Start(void){

}

void SW_Timer::Reset(void){
	if(SW_TmrTime[_event_N] == 0){
		SW_TmrFunc[_event_N] = _TmrFunc;
		SW_TmrTime[_event_N] = _TmrTime;

		StartTmr(_event_N);
		setTmrUsed(_event_N);
	}
}

/**
	@fn  TimerPause
	@brief Pausa el conteo del tiempo del número de contador especificado
 	@author Damian Melamed
 	@param [in] número de evento/contador.
 	@param [in] modo. USAR DEFINES "PAUSE" y "PLAY".
	@return 0 si el contador especificado no existe
*/
bool SW_Timer::Pause ( bool modo ){
	if(SW_TmrTime[_event_N]){
		if(modo) StartTmr(_event_N);
		else PauseTmr(_event_N);

		return true;
	}
	return false;
}

/**
	@fn  TimerStop
	@brief elimina el contador especificado
 	@author Damian Melamed
 	@param [in] número de evento/contador
	@return 0 si el contador especificado no existe
*/
bool SW_Timer::Stop (){
	if(SW_TmrTime[_event_N]){
		SW_TmrTime[_event_N] = 0;
		PauseTmr(_event_N);
		SW_TmrFunc[_event_N] = nullptr;

		clrTmrUsed(_event_N);
		return true;
	}
	return false;
}


/**
	@fn  TimerSet
	@brief setea un nuevo tiempo de conteo a un contador ya creado
 	@author Damian Melamed
 	@param número de evento/contador.
 	@param nuevo tiempo
	@return -1 si el contador especificado no existe o no fue creado con TimerStart()
*/
bool SW_Timer::Set (uint16_t t ){
	if(SW_TmrTime[_event_N]){
		SW_TmrTime[_event_N] = t;
		return true;
	}
	return false;
}


/**
	@fn  TimerGet
	@brief getea el tiempo restante para que termine el contador
 	@author Damian Melamed
 	@param [in] número de evento/contador.
 	@param [out] tiempo restante para que termine el contador
	@return -1 si el contador especificado no existe o no fue creado con TimerStart()
*/
int16_t SW_Timer::Get(){
	if(TmrUsedState(_event_N)){
		return SW_TmrTime[_event_N];
	}
	return -1;
}

//<<<<<<<<<<<<<<<<<funciones para funcionamiento>>>>>>>>>>>>>>>>>>>//

/**
	@fn  TimerRun
	@brief ejecuta la funcion correpondiente cuando termina la cuenta
	@Pparam [in] número de evento/contador.
 	@author Damian Melamed
*/
void SW_Timer::Run ( void ){
	if(SW_TmrPlay){	//si algun software timer está siendo utilizado. Si no, no recorre el for loop
		for(uint8_t i = 0; i < N_TIMERS; i ++){
			if((SW_TmrTime[i]) && (TmrPlayState(i))){
				SW_TmrTime[i]--;
				if(!SW_TmrTime[i]){
					SW_TmrFunc[i]();
				}
			}
		}
	}
}



