/*
 * System.h
 *
 *  Created on: 30 dic. 2020
 *      Author: usuario
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f103x6.h"

/******  types definitions  ***********************************************************************/

typedef	short unsigned int	uint16_t;
typedef	short int			  int16_t;
typedef	unsigned char		uint8_t ;


#define     __R             volatile const 	//< solo lectura
#define 	__W     		volatile 		//< solo escritura
#define 	__RW            volatile 		//< lectura / escritura


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_H_ */
