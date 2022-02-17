#include <tinyprintf.h>
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

using namespace std;

//Hardware declaration
OutputPin led(PORTC, 13, OutputPin::PUSH_PULL);

//Variable declaration

volatile uint16_t res[4];

void sendVal(void) {
    led = !led();
    ADC::readAll();

    Serial::printBlocking(res[0]);
    Serial::printBlocking("\t");
    Serial::printBlocking(res[1]);
    Serial::printBlocking("\n");

    Serial::printBlocking(res[2]);
    Serial::printBlocking("\t");
    Serial::printBlocking(res[3]);
    Serial::printBlocking("\n");

    Serial::printBlocking("\n");
}

void ms_func(void) {
}

extern "C" void putc(void* p, char c) {
    while ((USART1->SR & USART_SR_TXE) == 0) continue;
    USART1->DR = c;
}

int main() {
    //RHAL definition. Must be At the top
    RHAL hal;

    init_printf(NULL, putc);

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
    //Serial::printBlocking("Hola!\n");

        //cout << "hola" << endl;
    //printf("%X\t%X\n", ADC1->SQR3, ADC2->SQR3);

    /*while (1) {
        hal.tick(&ms_func);

        timer.loop();
    }*/
}