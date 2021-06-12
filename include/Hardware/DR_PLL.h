/*
 * DR_PLL.h
 *
 *  Created on: Dec 30, 2020
 *  Author: Damian Melamed
 */

#ifndef DR_H_DR_PLL_H_
#define DR_H_DR_PLL_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/
enum{APB1,APB2,AHB};

enum APB2_bits{
	AFIO_APB = 0,
	GPIOA_APB = 2,
	GPIOB_APB = 3,
	GPIOC_APB = 4,

	ADC1_APB = 9,
	ADC2_APB = 10,
	TIM1_APB = 11,
	SPI1_APB = 12,

	USART1_APB = 14,
};

enum APB1_bits{
	TIM2_APB = 0,
	TIM3_APB = 1,

	WWDG_APB = 11,

	SPI2_APB = 14,

	USART2_APB = 17,
	//USART3_APB = 18,

	I2C1_APB = 21,
	I2C2_APB = 22,
	USB_APB = 23,

	CAN_APB = 25,

	BKP_APB = 27,
	PWR_APB = 28,
	DAC_APB = 29
};

enum AHB_bits{
	DMA1_APB = 0,
};

enum APB_divFactor{APB_DIV_NONE, APB_DIV_2 = 4, APB_DIV_4, APB_DIV_8, APB_DIV_16};
enum ADC_divFactor{ADC_DIV_2, ADC_DIV_4, ADC_DIV_6, ADC_DIV_8};
enum USB_divFactor{USB_DIV_1_5, USB_DIV_NONE};
enum AHB_divFactor{AHB_DIV_NONE,
	AHB_DIV_2 = 8,
	AHB_DIV_4,
	AHB_DIV_8,
	AHB_DIV_16,
	AHB_DIV_64,
	AHB_DIV_128,
	AHB_DIV_256,
	AHB_DIV_512
};

enum FLASH_latencyWS{FLASH_LATENCY_24MHZ = 0, FLASH_LATENCY_48MHZ = 1, FLASH_LATENCY_72MHZ = 2};
enum SYSCLK_src{SYSCLK_HSI, SYSCLK_HSE, SYSCLK_PLL};

enum PLL_src{PLL_SRC_HSI,PLL_SRC_HSE};
enum PLL_multFactor{
	PLL_MULT_2 = 0,
	PLL_MULT_3,
	PLL_MULT_4,
	PLL_MULT_5,
	PLL_MULT_6,
	PLL_MULT_7,
	PLL_MULT_8,
	PLL_MULT_9,
	PLL_MULT_10,
	PLL_MULT_11,
	PLL_MULT_12,
	PLL_MULT_13,
	PLL_MULT_14,
	PLL_MULT_15,
};
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
//Inline functions
void CLK_enableHSE(void);
void CLK_setPrescaler(uint8_t _AHB, uint8_t _APB1, uint8_t _APB2, uint8_t _ADC, uint8_t _USB);
void CLK_FLASH_setLatency(uint8_t waitSatate);
void CLK_FLASH_enPrefetch(void);
void CLK_setPLL_mult(uint8_t mult);
void CLK_setPLL_src(uint8_t src);
void CLK_PLL_HSEprediv(uint8_t e);
void CLK_enablePLL();
void CLK_setSystemCLK(uint8_t src);

void APB_Enable(uint8_t reg, uint8_t bit);
void APB_Disable(uint8_t reg, uint8_t bit);

#ifdef __cplusplus
}
#endif

#endif /* DR_H_DR_PLL_H_ */
