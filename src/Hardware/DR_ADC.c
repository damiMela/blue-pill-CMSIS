#include <Hardware/DR_ADC.h>

ADC_TypeDef* const ADC[] = {ADC1, ADC2};

extern inline void ADC_enableInterrupt(uint8_t adcN) {
    ADC[adcN]->CR1 |= ADC_CR1_EOCIE;
}

extern inline void ADC_setSamplingRate(uint8_t adcN, uint8_t chn, uint8_t rate) {
    if (chn <= 9)
        ADC[adcN]->SMPR2 |= (rate << (chn * 3));
    else
        ADC[adcN]->SMPR1 |= (rate << ((chn - 10) * 3));
}

extern inline void ADC_setConversionSequence(uint8_t adcN, uint8_t chn, uint8_t pos) {
    if (pos <= 5)
        ADC[adcN]->SQR3 |= (chn << (pos * 5));
    else if (pos <= 11)
        ADC[adcN]->SQR2 |= (chn << ((pos - 6) * 5));
    else if (pos <= 15)
        ADC[adcN]->SQR1 |= (chn << ((pos - 12) * 5));
}

extern inline void ADC_setConversionLength(uint8_t adcN, uint8_t len) {
    ADC[adcN]->SQR1 &= ~(0b1111 << ADC_SQR1_L_Pos);
    ADC[adcN]->SQR1 |= ((len - 1) << ADC_SQR1_L_Pos);
}

extern inline void ADC_enable(uint8_t adcN) {
    ADC[adcN]->CR2 |= ADC_CR2_ADON;
    ADC[adcN]->CR2 |= ADC_CR2_RSTCAL;
    while (ADC[adcN]->CR2 & ADC_CR2_RSTCAL) continue;
    ADC[adcN]->CR2 |= ADC_CR2_CAL;
    while (ADC[adcN]->CR2 & ADC_CR2_CAL) continue;
}

extern inline void ADC_enableContinuousConversion(uint8_t adcN) {
    ADC[adcN]->CR2 |= ADC_CR2_CONT;
}

extern inline void ADC_enableScanMode(uint8_t adcN) {
    ADC[adcN]->CR1 |= ADC_CR1_SCAN;
}

extern inline void ADC_enableDMA(uint8_t adcN) {
    ADC[adcN]->CR2 |= ADC_CR2_DMA;
}

extern inline void ADC_enableDualMode(void) {
    ADC1->CR1 |= (0b0110 << ADC_CR1_DUALMOD_Pos);
}

extern inline void ADC_enableActivateBySoftware(uint8_t adcN) {
    ADC[adcN]->CR2 |= ADC_CR2_EXTTRIG;
    ADC[adcN]->CR2 |= ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0;
}

extern inline void ADC_startConversion(uint8_t adcN) {
    ADC[adcN]->CR2 |= ADC_CR2_SWSTART;
}

extern inline void ADC_clearEOCFlag(uint8_t adcN) {
    ADC[adcN]->SR &= ~ADC_SR_EOC;
}

uint16_t ADC_getData(uint8_t adcN) {
    return ADC[adcN]->DR;
}

extern inline uint8_t SysFlag_ADC() {
    uint8_t r = main_flags.ADC_EOF;
    main_flags.ADC_EOF = 0;
    return r;
}

void ADC1_2_IRQHandler(void) {
    if (ADC[_ADC1]->SR & ADC_SR_EOC)
        ADC[_ADC1]->SR &= ~ADC_SR_EOC;
    main_flags.ADC_EOF = 1;
}