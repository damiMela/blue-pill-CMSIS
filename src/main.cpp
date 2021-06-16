//include library
#include <RHAL.h>

//Hardware declaration
OutputPin led(PORTC, 13, OutputPin::PUSH_PULL); //builtin LED
InputPin btn(PORTA, 7, InputPin::PULLUP);

//blink function to be called every 1 millisecond
void turnOffLed(){
    led = false;    //turn the led off after a period of time.
}

int main() {
    //RHAL definition. Must be At the top
    RHAL hal;

    //Hardware inicialization
    led.init();
    btn.init();
    
    led = false; //start with the led OFF 

    //Create a software timer. It will not start counting until the init() function is called 
    SoftwareTimer ledTimer(3000, turnOffLed); //count 3 seconds and then call the function

    while (1) {
        hal.tick(); //system update. Must be at the top of the code     

        //if the button is pressed, the led will be turned on for 3 seconds. Then, it will turn off
        if(btn() && ledTimer.ended()){ 
            ledTimer.init();    //make the timer start counting
            led = true;         //turn the led ON
        }
       
    }
}