/*
 * DR_Systick.c
 *
 *  Created on: Dec 30, 2020
 *  Author: Damian Melamed
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <Hardware/DR_Systick.h>
#include <Hardware/DR_GPIO.h>


#ifdef __cplusplus
extern "C" {
#endif

/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/



/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
uint32_t msTicks = 0; 
/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
/** @brief 	Systick handler
 *
 */

void SysTick_Handler(void) {   /* startup file startup_stm32f103xx.s for SysTick vector */ 
  msTicks++;                                              
}

#ifdef __cplusplus
}
#endif
