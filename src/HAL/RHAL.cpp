/*
 * RHAL.cpp
 *
 *  Created on: Jan 6, 2021
 *      Author: Damián
 */
#include <HAL/RHAL.h>

//Hardware includes
#include <Hardware/DR_PLL.h>
#include <Hardware/DR_Systick.h>

volatile Flags_t main_flags;//variable global para flags

RHAL::RHAL(){
	init_CLK();
    SysTick_Config(SystemCoreClock / 1000);
    NVIC_SetPriority(SysTick_IRQn, 16);
    NVIC_EnableIRQ(SysTick_IRQn);

    APB_Enable(APB2, GPIOA_APB);
    APB_Enable(APB2, GPIOB_APB);
    APB_Enable(APB2, GPIOC_APB);

	main_flags.Systick_ms = 0;
	main_flags.SW_timer_used = 0;
}

void RHAL::init_CLK(){
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


void RHAL::do_every_1ms(void (* func )(void)){
	if(one_ms_passed()){
		if(main_flags.SW_timer_used)
			SW_Timer::Run();

		func();
	}
}
