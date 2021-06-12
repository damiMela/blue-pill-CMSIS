#include <Hardware/DR_ADC.h>

extern inline void ADC_InterruptEnable(void){
    ADC1->CR1 |= ADC_CR1_EOCIE;    
}

extern inline void ADC_setSamplingRate(uint8_t chn, uint8_t rate){
    if(chn <= 9)
        ADC1->SMPR2 |= (rate << (chn * 3));
    else
        ADC1->SMPR1 |= (rate << ((chn - 10) *3));
}

extern inline void ADC_setConvSequence(uint8_t chn, uint8_t pos){
    if(pos <= 5)
        ADC1->SQR3 |= (chn << (pos * 5));
    else if(pos <= 11)
        ADC1->SQR2 |= (chn << ((pos - 6) * 5));
    else if(pos <= 15)
        ADC1->SQR1 |= (chn << ((pos - 12) * 5));
}

extern inline void ADC_setConvLenght(uint8_t len){
    ADC1->SQR1 &= ~(0b1111 << ADC_SQR1_L_Pos);
    ADC1->SQR1 |= ((len-1) << ADC_SQR1_L_Pos);
}

extern inline void ADC_on(void){
    ADC1->CR2 |= ADC_CR2_ADON;
}

extern inline void ADC_caibrate(void){
    ADC1->CR2 |= ADC_CR2_CAL;
}

extern inline void ADC_contConvEnable(void){
    ADC1->CR2 |= ADC_CR2_CONT;
}

extern inline void ADC_ScanModeEnable(void){
    ADC1->CR1 |= ADC_CR1_SCAN;
}

extern inline void ADC_DMAEnable(void){
    ADC1->CR2 |= ADC_CR2_DMA;
}

uint16_t ADC_getData(void){
    return ADC1->DR;
}