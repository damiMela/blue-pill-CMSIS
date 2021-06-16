/*
 * SoftwareTimer.cpp
 *
 *  Created on: 5 ene. 2021
 *      Author: usuario
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <HAL/SoftwareTimer.h>

/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/
#define TIMER_PAUSE(b)		(SoftwareTimer::_runningTimers &= ~(1 << b))
#define TIMER_START(b)		(SoftwareTimer::_runningTimers |= (1 << b))
#define TIMER_IS_RUNNING(b)	((SoftwareTimer::_runningTimers >> b) & 0x01)

#define TIMER_SET_USED(b)	(SoftwareTimer::_usedTimers |= (1 << b))
#define TIMER_CLEAR_USED(b)	(SoftwareTimer::_usedTimers &= ~(1 << b))
#define TIMER_IS_USED(b)	((SoftwareTimer::_usedTimers >> b) & 0x01)

#define TIMER_SET_AUTODELETE(b)		(SoftwareTimer::_deleteAtEnd |= (1 << b))
#define TIMER_CLEAR_AUTODELETE(b)	(SoftwareTimer::_deleteAtEnd &= ~(1 << b))
#define TIMER_AUTODELETES(b)		((SoftwareTimer::_deleteAtEnd >> b) & 0x01)
/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/
uint16_t SoftwareTimer::_timerCounters[ N_TIMERS ] = {0};
void (*SoftwareTimer::_timerFunctions[ N_TIMERS ])(void) = {nullptr};
uint32_t SoftwareTimer::_usedTimers = 0;
uint32_t SoftwareTimer::_runningTimers = 0;
uint32_t SoftwareTimer::_deleteAtEnd = 0;
/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

/**
	@fn  Timer
	@brief Inicializa un contador 
 	@author Damian Melamed
 	@param [in] Tiempo en milisegundos.
 	@param [in] Función de finalización
	@return Objeto SoftwareTimer
*/
SoftwareTimer::SoftwareTimer(uint16_t time, void (*function)(void), bool autoDelete){
	_time = time;
	_function = function;
	_autoDelete = autoDelete;
	
}

bool SoftwareTimer::init(void){
	for(uint8_t i = 0; i < N_TIMERS; i++){
		if(TIMER_IS_USED(i)) break;

		_index = i;
		_timerFunctions[_index] = _function;
		_timerCounters[_index] = _time;

		TIMER_START(_index);
		TIMER_SET_USED(_index);
		TIMER_SET_AUTODELETE(_autoDelete);
		return true;
	}
	return false;
}

void SoftwareTimer::loop(void){
	if(_timerCounters[_index] == 0){
		_timerFunctions[_index] = _function;
		_timerCounters[_index] = _time;

		TIMER_START(_index);
		TIMER_SET_USED(_index);
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
bool SoftwareTimer::pause ( bool modo ){
	if(_timerCounters[_index]){
		if(modo) TIMER_START(_index);
		else TIMER_PAUSE(_index);

		return true;
	}
	return false;
}

/**
	@fn  Stop
	@brief elimina el contador especificado
 	@author Damian Melamed
 	@param [in] número de evento/contador
	@return 0 si el contador especificado no existe
*/
bool SoftwareTimer::deleteTimer(uint8_t timerN){
	if(TIMER_IS_USED(timerN)){
		_timerCounters[timerN] = 0;
		TIMER_PAUSE(timerN);
		_timerFunctions[timerN] = nullptr;

		TIMER_CLEAR_USED(timerN);
		return true;
	}
	return false;
}

/**
	@fn  Stop
	@brief elimina el contador
 	@author Damian Melamed
	@return 0 si el contador especificado no existe
*/
bool SoftwareTimer::stop (){
	return deleteTimer(_index);
}


/**
	@fn  TimerSet
	@brief setea un nuevo tiempo de conteo a un contador ya creado
 	@author Damian Melamed
 	@param número de evento/contador.
 	@param nuevo tiempo
	@return -1 si el contador especificado no existe o no fue creado con TimerStart()
*/
bool SoftwareTimer::set(uint16_t time){
	if(_timerCounters[_index]){
		_timerCounters[_index] = time;
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
int16_t SoftwareTimer::get(){
	if(TIMER_IS_USED(_index)){
		return _timerCounters[_index];
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
void SoftwareTimer::tick ( void ){
	if(!_usedTimers) return; // si no hay timers usados, salir
	if(!_runningTimers) return;	// si no hay timers corriendo, salir

	for(uint8_t i = 0; i < N_TIMERS; i++){
		if(!TIMER_IS_RUNNING(i)) continue;
		_timerCounters[i]--;

		if(!_timerCounters[i]){
			TIMER_PAUSE(i);
			_deleteAtEnd |= 1;
			_timerFunctions[i]();
			if( TIMER_AUTODELETES(i)) deleteTimer(i);
		}
	}
}

bool SoftwareTimer::ended(){
	if(get() == 0) return true;
}