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

/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

/** @brief Iniciializa y configura la entrada de clock, el PLL y los clocks de los perifericos*/
extern inline void CLK_enableHSE(void) {
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
}

/** @brief 	setea los preescalers de los perifericos
 *  @param	AHB preescaler. usar defines AHB_DIV_x
 *  @param 	APB1 preescaler. usar defines APB_DIV_x
 *  @param 	APB2 preescaler. usar defines APB_DIV_x
 *  @param	ADC preescaer. usar defines ADC_DIVx
 *  @param	USB preescaer. usar defines USB_DIVx
 */
extern inline void CLK_setPrescaler(uint8_t _AHB, uint8_t _APB1, uint8_t _APB2, uint8_t _ADC, uint8_t _USB){
	RCC->CFGR |= (_AHB << RCC_CFGR_HPRE_Pos); //72MHz
	RCC->CFGR |= (_APB1 << RCC_CFGR_PPRE1_Pos); //APB1. 36Mhz
	RCC->CFGR |= (_APB2 << RCC_CFGR_PPRE2_Pos); //APB2. 72MHz
	RCC->CFGR |= (_ADC << RCC_CFGR_ADCPRE_Pos); //ADC. 12Mhz
	RCC->CFGR |= (_USB << RCC_CFGR_USBPRE_Pos);
}

/** @brief 	Setea la cantidad de waitsate's para la memoria flash. Cabmbia según la velocidad del Sysclock
 *  @param	waitsatate. Usar defines FLASH_LATENCY_x
 */
extern inline void CLK_FLASH_setLatency(uint8_t waitSatate){
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	FLASH->ACR |= (waitSatate << FLASH_ACR_LATENCY_Pos); //set 2 wait states for speeds > to 48MHz.
}

/** @brief 	Activa el prefetch de la memoria flash. */
extern inline void CLK_FLASH_enPrefetch(void){
	FLASH->ACR |= FLASH_ACR_PRFTBE; //Enable memory prefetch
}

/** @brief 	Setea el mutiplicador del PLL 
 *  @param	PLL multiplier. usar defines PLL_MULT_x
 */
extern inline void CLK_setPLL_mult(uint8_t mult){
	RCC->CFGR &= ~(RCC_CFGR_PLLMULL);
	RCC->CFGR |=  (mult << RCC_CFGR_PLLMULL9_Pos);
}

/** @brief 	Setea el source del PLL  
 *  @param	src. usar define PLL_SRC_x
 */
extern inline void CLK_setPLL_src(uint8_t src){
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC);
	RCC->CFGR |= (src << RCC_CFGR_PLLSRC_Pos);
}

/** @brief 	Permite activar la division X2 del HSE antes que la señal entre al PLL  
 *  @param	enable. (0 o 1)
 */
extern inline void CLK_PLL_HSEprediv(uint8_t e){
	RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);
	RCC->CFGR |= (e << RCC_CFGR_PLLXTPRE_Pos);
}

/** @brief 	Activa el PLL   */
extern inline void CLK_enablePLL(){
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
}

/** @brief 	Setea el source del sysclock(System clock)  
 *  @param	src. usar defines SYSCLK_x
 */
extern inline void CLK_setSystemCLK(uint8_t src){
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= (src << RCC_CFGR_SW_Pos);
	while(((RCC->CFGR & RCC_CFGR_SWS)>> RCC_CFGR_SWS_Pos)!= src);
}


/** @brief Habilitar los perifericos
 *  @param 	registro a escribir. USAR DEFINES APB1 y APB2
 *  @param  bit a escribir. Usar defines x_APB
 */
extern inline void APB_Enable(uint8_t reg, uint8_t bit){
	if(reg == APB1)
		RCC->APB1ENR |= (1 << bit);
	else if(reg == APB2)
		RCC->APB2ENR |= (1 << bit);
	else
		RCC->AHBENR |= (1<< bit);
}

/** @brief 	Deshablitar los perifericos
 *  @param 	registro a escribir. USAR DEFINES APB1 y APB2
 *  @param  bit a escribir. Usar defines x_APB
 */
extern inline void APB_Disable(uint8_t reg, uint8_t bit){
	if(reg == APB2)
		RCC->APB1RSTR &= ~(1 << bit);
	else
		RCC->APB2RSTR &= ~(1 << bit);
}

#ifdef __cplusplus
}
#endif

