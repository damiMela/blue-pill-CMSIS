#include <Hardware/DR_PLL.h>
#include <Hardware/DR_DMA.h>
#include <Hardware/DR_ADC.h>
#include <HAL/ADC.h>

#define ocd2int(ch) (ch >= '0' && ch <= '9') ? (ch - '0') : ((ch >= 'A' && ch <= 'H') ? (ch - 'A' + 10) : ((ch >= 'a' && ch <= 'h') ? (ch - 'a' + 10) : (-1)))
#define MAX_CHANNELS_PER_SEQUENCE 16

bool ADC::async = false;

uint8_t ADC::ADC_flag(){ return SysFlag_ADC();};

void ADC::setupDualModeScan(const char* channelsADC1, const char* channelsADC2, uint8_t sampleRate, bool async, volatile void* address) {
    enablePeripherals(true, true);

    uint8_t channels = setupSequence(_ADC1, channelsADC1, sampleRate);
    if (channels != setupSequence(_ADC2, channelsADC2, sampleRate))  // La cantidad de channels en ambos no es la misma.
        return;                                                      // Maybe setear un error flag en los system flags?

    ADC_enableScanMode(_ADC1);
    ADC_enableScanMode(_ADC2);

    ADC_enableDualMode();
    ADC_enableDMA(_ADC1);
    ADC_enableDMA(_ADC2);

    ADC_enableActivateBySoftware(_ADC1);
    ADC_enableActivateBySoftware(_ADC2);

    ADC_enableContinuousConversion(_ADC1);
    ADC_enableContinuousConversion(_ADC2);

    if (async) enableInterrupt();
    ADC::async = async;

    setupDMA(address, DMA_32_BITS, channels);

    ADC_enable(_ADC1);
    ADC_enable(_ADC2);
}

void ADC::setupSingleModeScan(const char* channelsADC1, uint8_t sampleRate, bool async, volatile void* address) {
    enablePeripherals(true, false);

    uint8_t channels = setupSequence(_ADC1, channelsADC1, sampleRate);

    ADC_enableScanMode(_ADC1);
    ADC_enableDMA(_ADC1);
    ADC_enableActivateBySoftware(_ADC1);

    if (async) enableInterrupt();
    ADC::async = async;
    
    setupDMA(address, DMA_16_BITS, channels);
    
    ADC_enable(_ADC1);
}


void ADC::readAll() {
    ADC_startConversion(_ADC1);

    if (!async)
        while (!ADC_conversionEnded(_ADC1)) continue;
}

void ADC::enablePeripherals(bool adc1, bool adc2) {
    if (adc1) APB_Enable(APB2, ADC1_APB);
    if (adc2) APB_Enable(APB2, ADC2_APB);
}

void ADC::enableInterrupt() {
    NVIC_EnableIRQ(ADC1_2_IRQn);
    ADC_enableInterrupt(_ADC1);
}

uint8_t ADC::setupSequence(uint8_t adc, const char* channels, uint8_t sampleRate) {
    int8_t scanner = -1;
    while (channels[++scanner] != '\0' && scanner < MAX_CHANNELS_PER_SEQUENCE) {
        uint8_t channel = ocd2int(channels[scanner]);
        ADC_setConversionSequence(adc, channel, scanner);
        ADC_setSamplingRate(adc, channel, sampleRate);
    }
    ADC_setConversionLength(adc, scanner);
    return scanner;
}

void ADC::setupDMA(volatile void* address, uint8_t size, uint8_t channels) {
    APB_Enable(AHB, DMA1_APB);

    DMA_setPeripheralAddress(0, &(ADC1->DR));
    DMA_setMemoryAddress(0, address);
    DMA_setDataN(0, channels);
    DMA_enableCircularMode(0);
    DMA_enableIncrementMemoryAddress(0);
    DMA_setMemoryDataSize(0, size);
    DMA_setPeripheralDataSize(0, size);
    DMA_enable(0);
}