#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/InputPin.h>
#include <HAL/SoftwareTimer.h>
#include <HAL/HardwareTimer.h>


//must be included last
#include <HAL/RHAL.h>

//Pin declaration
OutputPin led(PORTC, 13);
InputPin btn(PORTB, 12, InputPin::PULLUP);

//Variable declaration
volatile uint32_t ms_counter = 0;

void ms_func(void){
	ms_counter++;
}

void changeLed(void){
	static uint8_t state = 0;
	led = state;
	state = !state;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Inicialization
	led.init();
	
	//SoftwareTimer timer(500, &changeLed);

	//Pin initialization
    led = 0;

	//SoftwareTimer timer(500, &changeLed);
	for (uint16_t i = 0; i < 10000; i++);
	HardwareTimer tim2(_TIM1, 72, 1000, &ms_func);
	
	while(1){
		//hal.tick(&ms_func);
		//timer.reset(); //Se reinicia el timer apenas termina de ejecutarse.

		//if(ms_counter >= 6000) timer.stop(); //a los 6 segundos elimina el timer
		//led = !btn();
		if(ms_counter >= 1000){
			changeLed();
			ms_counter = 0;
		}

	}

	return 0;
}
