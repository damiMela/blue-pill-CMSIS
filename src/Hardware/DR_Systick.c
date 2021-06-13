/*
 * DR_Systick.c
 *
 *  Created on: Dec 30, 2020
 *  Author: Damian Melamed
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <Hardware/DR_Systick.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/
volatile uint32_t msTicks = 0;


/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
/** @brief 	Systick handler
 *
 */
void SysTick_Handler(void) {   /* startup file startup_stm32f103xx.s for SysTick vector */ 
  main_flags.Systick_ms = 1;	//pongo flag en 1 para avisar que pasó 1ms   
  msTicks++;                                      
}

#ifdef __cplusplus
}
#endif
