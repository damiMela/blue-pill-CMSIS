/*
 * RHAL.cpp
 *
 *  Created on: Jan 6, 2021
 *      Author: Damián
 */
#include <HAL/RHAL.h>
#include <Hardware/DR_PLL.h>
#include <Hardware/DR_Systick.h>

#include <HAL/SoftwareTimer.h>

volatile Flags_t main_flags;//variable global para flags

RHAL::RHAL(){
	_initClock();
    SysTick_Config(SystemCoreClock / 1000);
    NVIC_SetPriority(SysTick_IRQn, 16);
    NVIC_EnableIRQ(SysTick_IRQn);

    APB_Enable(APB2, GPIOA_APB);
    APB_Enable(APB2, GPIOB_APB);
    APB_Enable(APB2, GPIOC_APB);
	APB_Enable(APB2, AFIO_APB);

	main_flags.Systick_ms = 0;
}

void RHAL::_initClock(){
	//Enable External clock
	CLK_enableHSE();

	//Enable memory prefetch
	CLK_FLASH_enPrefetch();

	//Set Memory Latency
	CLK_FLASH_setLatency(FLASH_LATENCY_72MHZ);

	//RCC configure
	CLK_PLL_HSEprediv(0);
	CLK_setPLL_src(PLL_SRC_HSE);
	CLK_setPLL_mult(PLL_MULT_9);
	CLK_setPrescaler(AHB_DIV_NONE, APB_DIV_2, APB_DIV_NONE, ADC_DIV_6, USB_DIV_1_5);

	//Turn on PLL
	CLK_enablePLL();
	
	//Set PLL as CLK src
	CLK_setSystemCLK(SYSCLK_PLL);

    //NECESARY AFTER CHANGES TO CLK
    SystemCoreClockUpdate();
}

/**
	@fn  RHAL Tick
	@brief Ejecuta el tick de la RHAL y del programa del usuario en cada SysTick (1ms)
 	@author Damian Melamed
 	@param [in] Funcion de tick del programa del usuario.
*/
void RHAL::tick(void (* func )(void)){
	if(!_systick()) return;
	
	SoftwareTimer::tick();

	func();
}


void RHAL::delay(uint32_t ms){
	uint32_t finishMs = msTicks + ms;
	while(msTicks <= finishMs);
}

uint32_t RHAL::millis(void){
	return(msTicks);
}