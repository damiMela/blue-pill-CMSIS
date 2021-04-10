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

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
/** @brief 	Systick handler
 *
 */

void SysTick_Handler(void) {   /* startup file startup_stm32f103xx.s for SysTick vector */ 
  main_flags.Systick_ms = 1;	//pongo flag en 1 para avisar que pasó 1ms                                         
}

#ifdef __cplusplus
}
#endif
