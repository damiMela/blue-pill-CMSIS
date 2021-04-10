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

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
void Systick_init(void);
extern void SysTick_Handler(void);
extern uint8_t test;

#ifdef __cplusplus
}
#endif

#endif /* DR_H_DR_SYSTICK_H_ */
