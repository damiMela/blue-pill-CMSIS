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
enum ADC{_ADC1, _ADC2};
enum ADC_rates {CYCLES_1_5, CYCLES_7_5, CYCLES_13_5, CYCLES_28_5, CYCLES_41_5, CYCLES_55_5, CYCLES_71_5, CYCLES_239_5};
/*!-----------FUNCIONES PUBLCIAS---------------------------------------------------------------------*/

void ADC_InterruptEnable(uint8_t adcN);
void ADC_setSamplingRate(uint8_t adcN, uint8_t chn, uint8_t rate);
void ADC_setConvSequence(uint8_t adcN, uint8_t chn, uint8_t pos);
void ADC_setConvLenght(uint8_t adcN, uint8_t len);
void ADC_on(uint8_t adcN);
void ADC_caibrate(uint8_t adcN);
void ADC_contConvEnable(uint8_t adcN);
void ADC_ScanModeEnable(uint8_t adcN);
void ADC_DMAEnable(uint8_t adcN);
void ADC_dualModeENable(void);
void ADC_activateBySW(uint8_t adcN);
void ADC_startConvertion(uint8_t adcN);
uint16_t ADC_getData(uint8_t adcN);

#ifdef __cplusplus
}
#endif
#endif