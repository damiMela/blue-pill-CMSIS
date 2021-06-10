/*
 * HardwareTimer.cpp
 *
 *  Created on: 5 ene. 2021
 *      Author: Damian Melamed
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <HAL/HardwareTimer.h>
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
HardwareTimer::HardwareTimer(uint8_t timer, uint16_t presc, uint16_t val, void (*function)(void)){
	_timerN = timer;
    _timerFunctions[_timerN] = function;
	_presc = presc;
	_val = val;
    start();
}

void HardwareTimer::start(void){
    //Timer Cnfiguration
    switch(_timerN){
        case _TIM1: 	APB_Enable(APB2, TIM1_APB); break;
        case _TIM2: 	APB_Enable(APB1, TIM2_APB); break;
        case _TIM3: 	APB_Enable(APB1, TIM3_APB); break;
    }

	TIM_setPresc(_timerN, _presc);
	TIM_setPeriod(_timerN, _val);
	TIM_autoReload_en(_timerN);
	TIM_URS_en(_timerN); //Only over/underflow generates interrupts. if not, UpdateGeneration (UG) interrupts the timer
	TIM_Interrupt_en(_timerN); //enable update interrupt
	TIM_update_config(_timerN); //Update generation. After everything is set, configures the timer.
	TIM_counter_en(_timerN);

    switch(_timerN){
        case _TIM1: 	NVIC_EnableIRQ(TIM1_UP_IRQn);   break;
        case _TIM2: 	NVIC_EnableIRQ(TIM2_IRQn);      break;
        case _TIM3: 	NVIC_EnableIRQ(TIM3_IRQn);      break;
    }
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