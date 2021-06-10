/*
 * DR_GPIO.h
 *
 *  Created on: Dec 29, 2020
 *  Author: Damian Melamed
 */

#ifndef DR_H_DR_GPIO_H_
#define DR_H_DR_GPIO_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

enum ports_en{PORTA, PORTB, PORTC};

enum dir_en{INPUT, OUTPUT, ALTERNATE};
enum state_en{LOW, HIGH};

enum in_mode_en{INPUT_ANALOG = 0, INPUT_FLOATING = 1, INPUT_PULLUP = 2, INPUT_PULLDOWN = 2};
enum out_mode_en{OUTPUT_PUSHPULL, OUTPUT_OPENDRAIN};
enum alt_mode_en{ALTERNATE_PUSHPULL = 2, ALTERNATE_OPENDRAIN};
enum max_vel {MAX_VEL_10MHZ = 1, MAX_VEL_2MHZ, MAX_VEL_50MHZ};


/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
void GPIO_portEn(uint8_t port);
void GPIO_setDir(uint8_t port, uint8_t pin, uint8_t mode);
void GPIO_setPin(uint8_t port, uint8_t pin, uint8_t val);

uint8_t GPIO_getPin(uint8_t port, uint8_t pin);
uint8_t GPIO_getStatus(uint8_t port, uint8_t pin);

void GPIO_setInputMode(uint8_t port, uint8_t pin, uint8_t mode);
void GPIO_setOutputMode(uint8_t port, uint8_t pin, uint8_t mode);
void GPIO_setMaxOutputSpeed(uint8_t port, uint8_t pin, uint8_t vel);
void GPIO_setAltMode(uint8_t port, uint8_t pin, uint8_t mode);
void GPIO_setPull(uint8_t port, uint8_t pin, uint8_t set);

#ifdef __cplusplus
}
#endif

#endif /* DR_H_DR_GPIO_H_ */
