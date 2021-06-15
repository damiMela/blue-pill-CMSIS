#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <System.h>

extern "C" typedef void setConversionEnded();

class ADC {
   public:
    enum ADC_cycles{
        ADC_CYCLES_1_5,
        ADC_CYCLES_7_5,
        ADC_CYCLES_13_5,
        ADC_CYCLES_28_5,
        ADC_CYCLES_41_5,
        ADC_CYCLES_55_5,
        ADC_CYCLES_71_5,
        ADC_CYCLES_239_5
    };
    static void setupDualModeScan(const char* channelsADC1, const char* channelsADC2, uint8_t sampleRate, bool async, volatile void* address);
    static void setupSingleModeScan(const char* channelsADC1, uint8_t sampleRate, bool async, volatile void* address);
    static void setupContinuousMode(const char* channelsADC1, uint8_t sampleRate);
    static void readAll();
    static uint8_t ADC_flag();

   private:
    static void enablePeripherals(bool adc1, bool adc2);
    static void enableInterrupt();
    static uint8_t setupSequence(uint8_t adc, const char* channels, uint8_t sampleRate);
    static void setupDMA(volatile void* address, uint8_t size, uint8_t channels);
    static bool async;
};

#endif