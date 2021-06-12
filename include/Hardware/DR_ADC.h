/*
 * DR_GPIO.h
 *
 *  Created on: Jun 11, 2021
 *  Author: Damian Melamed
 */

#ifndef DR_H_DR_ADC_H_
#define DR_H_DR_ADC_H_
/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
enum ADC_rates {CYCLES_1_5, CYCLES_7_5, CYCLES_13_5, CYCLES_28_5, CYCLES_41_5, CYCLES_55_5, CYCLES_71_5, CYCLES_239_5};
/*!-----------FUNCIONES PUBLCIAS---------------------------------------------------------------------*/

void ADC_InterruptEnable(void);
void ADC_setSamplingRate(uint8_t chn, uint8_t rate);
void ADC_setConvSequence(uint8_t chn, uint8_t pos);
void ADC_setConvLenght(uint8_t len);
void ADC_on(void);
void ADC_caibrate(void);
void ADC_contConvEnable(void);
void ADC_ScanModeEnable(void);
void ADC_DMAEnable(void);
uint16_t ADC_getData(void);

#ifdef __cplusplus
}
#endif
#endif