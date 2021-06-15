#include <stdio.h>
#include <RHAL.h>

//Hardware declaration
OutputPin led(PORTC, 13, OutputPin::PUSH_PULL);
InputPin a1(PORTB, 0, InputPin::PULLDOWN);
InputPin a2(PORTB, 1, InputPin::PULLDOWN);
InputPin a3(PORTA, 6, InputPin::PULLDOWN);
InputPin a4(PORTA, 7, InputPin::PULLDOWN);

//Variable declaration

volatile uint32_t res[2];
volatile uint16_t res_2[3];
volatile uint8_t irr = 0;

void ms_func(void) {
}

void sendVal(void) {
    led = !led();
    ADC::readAll();
    while (!ADC::ADC_flag()) continue;
    uint32_t buffer = res_2[0];  // PARA NO MOLESTAR AL DMA

    Serial::printBlocking(buffer);
    Serial::printBlocking("\t");

    buffer = res_2[1];
    Serial::printBlocking(buffer);
    Serial::printBlocking("\t");

    buffer = res_2[2];
    Serial::printBlocking(buffer);
    Serial::printBlocking("\t");
    Serial::printBlocking("\n");
}

int main() {
    //RHAL definition. Must be At the top
    RHAL hal;

    //timer initialization
    Serial::init(9600);
    SoftwareTimer timer(100, &sendVal);

    led.init();
    led = 1;

    //set adc pins to input push-pull (is done by setting input pulldown)
    a1.init();
    a2.init();
    a3.init();
    a4.init();
    //ADC::setupDualModeScan("89", "98", CYCLES_28_5, false, &res);
    ADC::setupSingleModeScan("897", ADC::ADC_CYCLES_28_5, true, &res_2);

    for (uint32_t i = 0; i < 7200000; i++) __NOP();  //delay para esperar a que se inicialize el serial console
    Serial::printBlocking("Hola!\n");

    //printf("%X\t%X\n", ADC1->SQR3, ADC2->SQR3);

    while (1) {
        hal.tick(&ms_func);

        timer.loop();
    }
}