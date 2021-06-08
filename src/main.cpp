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

	//Pin initialization
	led.init();
    led = 0;
	

	SoftwareTimer timer(1000, &changeLed);
	HardwareTimer HWtimer(_TIM1, 72, 1000, &changeLed);
	
	while(1){
		//------Test do a function every 1 ms
		//hal.tick(&ms_func);
		
		//------Test Software timer
		//hal.tick(&ms_func);
		//timer.loop(); //Se reinicia el timer apenas termina de ejecutarse.
		//if(ms_counter >= 10000) timer.stop(); //a los 6 segundos elimina el timer

		//------Test GPIO
		//led = !btn();

		//-------Test Hardware Timer (comentar para prueba de software timer)
		/*
		if(ms_counter >= 1000){
			changeLed();
			ms_counter = 0;
		}
		*/

	}

	return 0;
}
