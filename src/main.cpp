//include library
#include <RHAL.h>

//Hardware declaration
    HardwareTimer tim(HardwareTimer::TIMER3, 72, 100);
    PWM test(tim, PWM::CHANNEL_2, PORTA, 7);


//blink function to be called every 1 millisecond

int main() {
    //RHAL definition. Must be At the top
    RHAL hal;
    Serial::init(9600);

    test.init();
    test.setDutyCycle(10);
    printf("Welcome!\n");

    while (1) {
        hal.tick();  //system update. Must be at the top of the code

        printf("Millis: %lu\r", RHAL::millis());
    }
}