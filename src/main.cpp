#include "System.h"
#include <HAL/OutputPin.h>
#include <Hardware/DR_Systick.h>

void delay_ms(uint32_t val);



int main()
{
	//Enable External clock
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));

	//Enable memory prefetch
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	//Set Memory Latency
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t)0x02; //set latency to 2;

	//RCC configure
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL); //reset bits
	RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	//Turn on PLL
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
	
	//Set PLL as CLK src
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));

	SystemCoreClockUpdate();
	if(SysTick_Config(SystemCoreClock / 1000)){
		//capture error
		while(1);
	}

	 NVIC_SetPriority(SysTick_IRQn, 16);
	 NVIC_EnableIRQ(SysTick_IRQn);




    OutputPin Led(PORTC, 13);
    Led = false;
	msTicks = 0;
	bool led_state = false;

	while(1){
		if(msTicks >= 1000){
			led_state = !led_state;	
			msTicks = 0;
		}
		Led = led_state;


		
		

	}


}



void delay_ms(uint32_t val){
	msTicks = 0;
}
                                           


