#include <HAL/HardwareTimer.h>
#include <HAL/InputPin.h>
#include <HAL/OutputPin.h>
#include <HAL/PWM.h>
#include <HAL/Serial.h>
#include <HAL/SoftwareTimer.h>
#include <HAL/ADC.h>
#include <stdio.h>

#include "System.h"

//must be included last
#include <HAL/RHAL.h>
#include <Hardware/DR_ADC.h>
#include <Hardware/DR_DMA.h>
#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_PLL.h>

//Hardware declaration
OutputPin led(PORTC, 13, OutputPin::PUSH_PULL);

//Variable declaration

volatile uint32_t res = 0;
volatile uint8_t irr = 0;

void ms_func(void) {
}

void sendVal(void) {
    led = !led();
    ADC::readAll();
    while (!SysFlag_ADC()) continue;
    uint32_t buffer = res;  // PARA NO MOLESTAR AL DMA
    uint16_t val1, val2;
    val2 = buffer >> 16;
    val1 = buffer & 0xFFFF;
    Serial::print(val1);
    Serial::print("\t");
    Serial::println(val2);
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

    ADC::setupDualModeScan("8", "9", CYCLES_28_5, true, &res);

    while (1) {
        hal.tick(&ms_func);
        timer.loop();
    }
}