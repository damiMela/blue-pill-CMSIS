/*
 * System.h
 *
 *  Created on: 30 dic. 2020
 *      Author: usuario
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <tinyprintf.h>
#include <stm32f1xx.h>

#ifdef __cplusplus
extern "C" {
#endif

/******  types definitions  ***********************************************************************/
//typedef	unsigned int		uint32_t;
//typedef	signed int			int32_t;
typedef short unsigned int uint16_t;
typedef short int int16_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;

#define __R volatile const  //< solo lectura
#define __W volatile        //< solo escritura
#define __RW volatile       //< lectura / escritura

/******  flags definitions * ***********************************************************************/
//defino mapa de bits para flags globales
typedef struct {
    volatile uint8_t Systick_ms : 1;
    volatile uint8_t ADC_EOF : 1;
} Flags_t;

extern volatile Flags_t main_flags;  //variable global para flags

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_H_ */
