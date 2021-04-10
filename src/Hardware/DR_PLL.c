/*
 * DR_PLL.c
 *
 *  Created on: Dec 30, 2020
 *  Author: Damian Melamed
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <Hardware/DR_PLL.h>
#include <System.h>
#ifdef __cplusplus
extern "C" {
#endif

/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/


/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/
typedef struct{
	uint32_t HSI_on:	1;
	uint32_t HSI_ready: 1;
	uint32_t RESERVED0: 1;
	uint32_t HSI_trim:  5;
	uint32_t ISI_calib: 8;
	uint32_t HSE_on:	1;
	uint32_t HSE_ready:	1;
	uint32_t HSE_bypass:1;
	uint32_t CSS_on:	1;
	uint32_t RESERVED1:	4;
	uint32_t PLL_on:	1;
	uint32_t PLL_ready:	1;
	uint32_t RESERVED2:	6;
} RCC_CR_t;


typedef struct{
	uint32_t SysClk_sw:		2; //SW. system clock switch
	uint32_t SysClk_sw_stat:2; //SWS system clock switch status
	uint32_t AHB_presc:		4; //HPRE. AHB preescaler
	uint32_t APB1_presc:	3; //PPRE1. APB1 low-speed preescaler
	uint32_t APB2_presc:	3; //PPRE2. APB2 high-speed preescaler
	uint32_t ADC_presc:		2; //ADCPRE. adc preescaler
	uint32_t PLL_src:		1; //PLLSRC. PLL source
	uint32_t HSE_PLL_prediv:	1; //PLLXTPRE. HSE dividier for
	uint32_t PLL_mult:		4; //PLLMUL. PLL multiplication factor
	uint32_t USB_presc:		1; //USBPRE. USB prescaler
	uint32_t RESERVED0:		1;
	uint32_t Clk_output:	3; //MCO. microcontroller clock output
	uint32_t RESERVED1:		5;
}RCC_CFGR_t;

typedef struct{
  __RW RCC_CR_t 	CR;
  __RW RCC_CFGR_t 	CFGR;
  __RW uint32_t 	CIR;
  __RW uint32_t 	APB2_RST;
  __RW uint32_t 	APB1_RST;
  __RW uint32_t 	AHB_EN;
  __RW uint32_t 	APB2_EN;
  __RW uint32_t 	APB1_EN;
  __RW uint32_t 	BDCR;
  __RW uint32_t 	CSR;

} RCC_t;
/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

/** @brief Iniciializa y configura la entrada de clock, el PLL y los clocks de los perifericos
 *
 */
extern inline void CLK_enableHSE(void) {
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
}

extern inline void CLK_setPrescaler(uint8_t _AHB, uint8_t _APB1, uint8_t _APB2, uint8_t _ADC, uint8_t _USB){
	RCC->CFGR |= (_AHB << RCC_CFGR_HPRE_Pos); //72MHz
	RCC->CFGR |= (_APB1 << RCC_CFGR_PPRE1_Pos); //APB1. 36Mhz
	RCC->CFGR |= (_APB2 << RCC_CFGR_PPRE2_Pos); //APB2. 72MHz
	RCC->CFGR |= (_ADC << RCC_CFGR_ADCPRE_Pos); //ADC. 12Mhz
	RCC->CFGR |= (_USB << RCC_CFGR_USBPRE_Pos);
}

extern inline void CLK_FLASH_setLatency(uint8_t waitSatate){
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	FLASH->ACR |= (waitSatate << FLASH_ACR_LATENCY_Pos); //set 2 wait states for speeds > to 48MHz.
}

extern inline void CLK_FLASH_enPrefetch(void){
	FLASH->ACR |= FLASH_ACR_PRFTBE; //Enable memory prefetch
}

extern inline void CLK_setPLL_mult(uint8_t mult){
	RCC->CFGR &= ~(RCC_CFGR_PLLMULL);
	RCC->CFGR |=  (mult << RCC_CFGR_PLLMULL9_Pos);
}

extern inline void CLK_setPLL_src(uint8_t src){
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
	RCC->CFGR |= (src << RCC_CFGR_PLLSRC_Pos);
}

extern inline void CLK_PLL_HSEprediv(uint8_t e){
	RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);
	RCC->CFGR |= (e << RCC_CFGR_PLLXTPRE_Pos);
}

extern inline void CLK_enablePLL(){
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
}

extern inline void CLK_setSystemCLK(uint8_t src){
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= (src << RCC_CFGR_SW_Pos);
	while(((RCC->CFGR & RCC_CFGR_SWS)>> RCC_CFGR_SWS_Pos)!= src);
}


/** @brief 	Permite hablitar los clocks de los perifericos
 *  @param 	registro a escribir. USAR DEFINES APB1 y APB2
 *  @param  bit a escribir
 *  @param 	habilitacion. 1 para habilitar, 0 para deshabilitar
 */
extern inline void APB_Enable(uint8_t reg, uint8_t bit){
	if(reg == APB1)
		RCC->APB1ENR |= (1 << bit);
	else
		RCC->APB2ENR |= (1 << bit);
}

extern inline void APB_Disable(uint8_t reg, uint8_t bit){
	if(reg == APB2)
		RCC->APB1RSTR &= ~(1 << bit);
	else
		RCC->APB2RSTR &= ~(1 << bit);
}

#ifdef __cplusplus
}
#endif

