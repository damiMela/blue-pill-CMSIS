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

enum ADC_modules {
    _ADC1,
    _ADC2
};

enum ADC_rates {
    CYCLES_1_5,
    CYCLES_7_5,
    CYCLES_13_5,
    CYCLES_28_5,
    CYCLES_41_5,
    CYCLES_55_5,
    CYCLES_71_5,
    CYCLES_239_5
};

#define ADC_conversionEnded(x)    (x==_ADC1) ? (ADC1->SR & ADC_SR_EOC) : (ADC2->SR & ADC_SR_EOC)
/*!-----------FUNCIONES PUBLCIAS---------------------------------------------------------------------*/

void ADC_enableInterrupt(uint8_t adcN);
void ADC_setSamplingRate(uint8_t adcN, uint8_t chn, uint8_t rate);
void ADC_setConversionSequence(uint8_t adcN, uint8_t chn, uint8_t pos);
void ADC_setConversionLength(uint8_t adcN, uint8_t len);
void ADC_enable(uint8_t adcN);
void ADC_enableContinuousConversion(uint8_t adcN);
void ADC_enableScanMode(uint8_t adcN);
void ADC_enableDMA(uint8_t adcN);
void ADC_enableDualMode(void);
void ADC_enableActivateBySoftware(uint8_t adcN);
void ADC_startConversion(uint8_t adcN);
void ADC_clearEOCFlag(uint8_t adcN);
uint16_t ADC_getData(uint8_t adcN);
uint8_t SysFlag_ADC();

#ifdef __cplusplus
}
#endif
#endif