/*
 * HardwareTimer.cpp
 *
 *  Created on: 5 ene. 2021
 *      Author: Damian Melamed
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <HAL/HardwareTimer.h>
#include <Hardware/DR_Timer.h>
#include <Hardware/DR_PLL.h>
/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/

/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/
static void (*_timerFunctions[ N_HARDWARE_TIMERS ])(void) = {nullptr};
/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

/**
	@fn  HardwareTimer
	@brief Inicializa un Timer 
 	@author Damian Melamed
 	@param [in]
 	@param [in] 
	@return Objeto HardwareTimer
*/
HardwareTimer::HardwareTimer(uint8_t timer, uint16_t presc, uint16_t period){
	_timerN = timer;
	_presc = presc;
	_period = period;
}

void HardwareTimer::init(void){
	switch(_timerN){
        case _TIM1: 	APB_Enable(APB2, TIM1_APB); break;
        case _TIM2: 	APB_Enable(APB1, TIM2_APB); break;
        case _TIM3: 	APB_Enable(APB1, TIM3_APB); break;
    }
	
	TIM_setPresc(_timerN, _presc);
	TIM_setPeriod(_timerN, _period);
	TIM_autoReload_en(_timerN);
}

void HardwareTimer::attachInterrupt(void (*function)(void)){
    _timerFunctions[_timerN] = function;
	
    //Timer Configuration
	TIM_URS_en(_timerN); //Only over/underflow generates interrupts. if not, UpdateGeneration (UG) interrupts the timer
	TIM_Interrupt_en(_timerN); //enable update interrupt

    switch(_timerN){
        case _TIM1: 	NVIC_EnableIRQ(TIM1_UP_IRQn);   break;
        case _TIM2: 	NVIC_EnableIRQ(TIM2_IRQn);      break;
        case _TIM3: 	NVIC_EnableIRQ(TIM3_IRQn);      break;
    }

	startTimer();
}

void HardwareTimer::setCallbackFunction(void (*function)(void)){
	_timerFunctions[_timerN] = function;
}

void HardwareTimer::startTimer(){
	TIM_update_config(_timerN); //Update generation. After everything is set, configures the timer.
	TIM_counter_en(_timerN);
}

#ifdef __cplusplus
extern "C"{
#endif

void TIM1_UP_IRQHandler(void){
    _timerFunctions[_TIM1]();
	TIM_rst_interrupt_flag(_TIM1);
}

void TIM2_IRQHandler(void){
    _timerFunctions[_TIM2]();
	TIM_rst_interrupt_flag(_TIM2);
}

void TIM3_IRQHandler(void){
    _timerFunctions[_TIM3]();
	TIM_rst_interrupt_flag(_TIM3);
}
#ifdef __cplusplus
}
#endif