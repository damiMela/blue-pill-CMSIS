#include <stdio.h>
#include "System.h"

#include <HAL/HardwareTimer.h>
#include <HAL/InputPin.h>
#include <HAL/OutputPin.h>
#include <HAL/PWM.h>
#include <HAL/Serial.h>
#include <HAL/SoftwareTimer.h>
#include <HAL/ADC.h>
#include <Hardware/DR_ADC.h>
#include <Hardware/DR_DMA.h>
#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_PLL.h>

#include <HAL/RHAL.h>

//Hardware declaration
OutputPin led(PORTC, 13, OutputPin::PUSH_PULL);

//Variable declaration

volatile uint32_t res[2];
volatile uint8_t irr = 0;

void ms_func(void) {
}

void sendVal(void) {
    led = !led();
    ADC::readAll();
    //while (!SysFlag_ADC()) continue;
    uint32_t buffer = res[0];  // PARA NO MOLESTAR AL DMA

    uint16_t val1, val2;
    val2 = buffer >> 16;
    val1 = buffer & 0xFFFF;
    Serial::printBlocking(val1);
    Serial::printBlocking("\t");
    Serial::printBlocking(val2);
    Serial::printBlocking("\n");

    buffer = res[1];
    val2 = buffer >> 16;
    val1 = buffer & 0xFFFF;
    Serial::printBlocking(val1);
    Serial::printBlocking("\t");
    Serial::printBlocking(val2);
    Serial::printBlocking("\n");
}

int main() {
    //RHAL definition. Must be At the top
    RHAL hal;

    //timer initialization
    Serial::init(9600);
    SoftwareTimer timer(1000, &sendVal);

    led.init();
    led = 1;

    //set adc pins to input push-pull (is done by setting input pulldown)
    GPIO_setDir(PORTB, 1, INPUT);
    GPIO_setInputMode(PORTB, 1, INPUT_PULLDOWN);
    GPIO_setDir(PORTB, 0, INPUT);
    GPIO_setInputMode(PORTB, 0, INPUT_PULLDOWN);

    ADC::setupDualModeScan("89", "98", CYCLES_28_5, false, &res);

    for (uint32_t i = 0; i < 7200000; i++) __NOP();  //delay para esperar a que se inicialize el serial console
    Serial::printBlocking("Hola!\n");

    //printf("%X\t%X\n", ADC1->SQR3, ADC2->SQR3);

    while (1) {
        hal.tick(&ms_func);

        timer.loop();
    }
}