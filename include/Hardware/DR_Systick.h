/*
 * DR_Systick.h
 *
 *  Created on: Dec 30, 2020
 *  Author: Damian Melamed
 */

#ifndef DR_H_DR_SYSTICK_H_
#define DR_H_DR_SYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/

/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/
                                      /* Variable to store millisecond ticks */
/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
extern volatile uint32_t msTicks;

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
extern void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* DR_H_DR_SYSTICK_H_ */
