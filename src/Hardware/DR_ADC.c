#include <Hardware/DR_ADC.h>

extern inline void ADC_InterruptEnable(uint8_t adcN){
    if(adcN == _ADC1) ADC1->CR1 |= ADC_CR1_EOCIE; 
    else ADC2->CR1 |= ADC_CR1_EOCIE;    
}

extern inline void ADC_setSamplingRate(uint8_t adcN, uint8_t chn, uint8_t rate){
    if(adcN == _ADC1){
        if(chn <= 9)    ADC1->SMPR2 |= (rate << (chn * 3));
        else    ADC1->SMPR1 |= (rate << ((chn - 10) *3));
    }
    else{
        if(chn <= 9)    ADC2->SMPR2 |= (rate << (chn * 3));
        else    ADC2->SMPR1 |= (rate << ((chn - 10) *3));
    }
}

extern inline void ADC_setConvSequence(uint8_t adcN, uint8_t chn, uint8_t pos){
    if(adcN == _ADC1){
        if(pos <= 5)    ADC1->SQR3 |= (chn << (pos * 5));
        else if(pos <= 11)  ADC1->SQR2 |= (chn << ((pos - 6) * 5));
        else if(pos <= 15)  ADC1->SQR1 |= (chn << ((pos - 12) * 5));
    }
    else{
        if(pos <= 5)    ADC2->SQR3 |= (chn << (pos * 5));
        else if(pos <= 11)  ADC2->SQR2 |= (chn << ((pos - 6) * 5));
        else if(pos <= 15)  ADC2->SQR1 |= (chn << ((pos - 12) * 5));
    }
}

extern inline void ADC_setConvLenght(uint8_t adcN, uint8_t len){
    if(adcN == _ADC1){
        ADC1->SQR1 &= ~(0b1111 << ADC_SQR1_L_Pos);
        ADC1->SQR1 |= ((len-1) << ADC_SQR1_L_Pos);
    }
    else{
        ADC2->SQR1 &= ~(0b1111 << ADC_SQR1_L_Pos);
        ADC2->SQR1 |= ((len-1) << ADC_SQR1_L_Pos);
    }
}

extern inline void ADC_on(uint8_t adcN){
    if(adcN == _ADC1){
        ADC1->CR2 |= ADC_CR2_ADON;
        ADC1->CR2 |= ADC_CR2_RSTCAL;
        while (ADC1->CR2 & ADC_CR2_RSTCAL) continue;
        ADC1->CR2 |= ADC_CR2_CAL;
        while (ADC1->CR2 & ADC_CR2_CAL) continue;
    }
    else{
        ADC2->CR2 |= ADC_CR2_ADON;
        ADC2->CR2 |= ADC_CR2_RSTCAL;
        while (ADC2->CR2 & ADC_CR2_RSTCAL) continue;
        ADC2->CR2 |= ADC_CR2_CAL;
        while (ADC2->CR2 & ADC_CR2_CAL) continue;
    }
}

extern inline void ADC_caibrate(uint8_t adcN){
    if(adcN == _ADC1)   ADC1->CR2 |= ADC_CR2_CAL;
    else                ADC2->CR2 |= ADC_CR2_CAL;
    
}

extern inline void ADC_contConvEnable(uint8_t adcN){
    if(adcN == _ADC1)   ADC1->CR2 |= ADC_CR2_CONT;
    else                ADC2->CR2 |= ADC_CR2_CONT;
}

extern inline void ADC_ScanModeEnable(uint8_t adcN){
    if(adcN == _ADC1)   ADC1->CR1 |= ADC_CR1_SCAN;
    else                ADC2->CR1 |= ADC_CR1_SCAN;
}

extern inline void ADC_DMAEnable(uint8_t adcN){
    if(adcN == _ADC1)   ADC1->CR2 |= ADC_CR2_DMA;
    else                ADC2->CR2 |= ADC_CR2_DMA;
}

extern inline void ADC_dualModeENable(void){
    ADC1->CR1 |= (0b0110 << ADC_CR1_DUALMOD_Pos); 
}

extern inline void ADC_activateBySW(uint8_t adcN){
    if(adcN == _ADC1){
        ADC1->CR2 |= ADC_CR2_EXTTRIG;
        ADC1->CR2 |= ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0;
    }
    else{
        ADC2->CR2 |= ADC_CR2_EXTTRIG;
        ADC2->CR2 |= ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0;
    }
}

extern inline void ADC_startConvertion(uint8_t adcN){
    if(adcN == _ADC1)   ADC1->CR2 |= ADC_CR2_SWSTART;
    else                ADC2->CR2 |= ADC_CR2_SWSTART;
}

uint16_t ADC_getData(uint8_t adcN){
    if(adcN == _ADC1)   return ADC1->DR;
    else                return ADC2->DR;
}