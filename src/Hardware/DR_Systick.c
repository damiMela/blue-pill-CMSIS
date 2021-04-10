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
uint8_t test = 0;
/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/

/** @brief 	Inicializa el systick con interrupciones cada 1ms
 *
 */
void Systick_init(void){
	SysTick_Config(SysTick->CALIB * 8);
}

/** @brief 	Systick handler
 *
 */
/*
void SysTick_Handler(void){
	test = !test;
	//main_flags.Systick_ms = 1;	//pongo flag en 1 para avisar que pasó 1ms
}*/

#ifdef __cplusplus
}
#endif
