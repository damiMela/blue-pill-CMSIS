#include "System.h"
#include <HAL/OutputPin.h>

void delay_ms(uint32_t val);
extern void SysTick_Handler(void);
uint32_t msTicks = 0;                                       /* Variable to store millisecond ticks */

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
	SysTick_Config(SystemCoreClock / 1000);




    OutputPin Led(PORTC, 13);
    Led = false;

	while(1){
		Led = true;
		delay_ms(20);
		Led = false;
		delay_ms(20);
	}


}
void SysTick_Handler(void)  {                               /* SysTick interrupt Handler. See startup file startup_LPC17xx.s for SysTick vector */ 
  msTicks++;                                                   
}

void delay_ms(uint32_t val){
	msTicks = 0;
	while(msTicks < val);
}
                                           


