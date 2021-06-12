/*
 * DR_GPIO.h
 *
 *  Created on: Jun 11, 2021
 *  Author: Damian Melamed
 */

#ifndef DR_H_DR_DMA_H_
#define DR_H_DR_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <System.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/
enum DMA_data_size{DMA_8_BITS, DMA_16_BITS, DMA_32_BITS};
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
void DMA_setPeriphAddr(uint8_t chn, uint32_t periph);
void DMA_setMemAddr(uint8_t chn, uint32_t mem);
void DMA_setDataN(uint8_t chn, uint8_t num);
void DMA_setCircularMode(uint8_t chn);
void DMA_incrementMemAddr(uint8_t chn);
void DMA_setPerihpSize(uint8_t chn, uint8_t size);
void DMA_setMemSize(uint8_t chn, uint8_t size);
void DMA_enable(uint8_t chn);

#ifdef __cplusplus
}
#endif
#endif