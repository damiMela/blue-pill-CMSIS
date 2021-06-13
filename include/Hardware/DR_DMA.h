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
enum DMA_data_size {
    DMA_8_BITS,
    DMA_16_BITS,
    DMA_32_BITS
};
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/

/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
void DMA_setPeripheralAddress(uint8_t chn, volatile void *periph);
void DMA_setMemoryAddress(uint8_t chn, volatile void *mem);
void DMA_setDataN(uint8_t chn, uint8_t num);
void DMA_enableCircularMode(uint8_t chn);
void DMA_enableIncrementMemoryAddress(uint8_t chn);
void DMA_setPeripheralDataSize(uint8_t chn, uint8_t size);
void DMA_setMemoryDataSize(uint8_t chn, uint8_t size);
void DMA_enable(uint8_t chn);

#ifdef __cplusplus
}
#endif
#endif