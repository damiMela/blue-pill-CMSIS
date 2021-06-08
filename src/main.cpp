#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/InputPin.h>
#include <HAL/SoftwareTimer.h>
#include <HAL/HardwareTimer.h>

#include <Hardware/DR_GPIO.h>
//must be included last
#include <HAL/RHAL.h>

//Pin declaration
OutputPin led(PORTB, 0);
InputPin btn(PORTB, 12, InputPin::PULLUP);

//Variable declaration
volatile uint32_t ms_counter = 0;
volatile uint8_t test = 0;

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

	//SoftwareTimer timer(1000, &changeLed);

	//-------Test Hardware Timer (comentar software timer)
	HardwareTimer HWtimer(_TIM2, 7200, 10000, &ms_func);

	while(1){
		//hal.tick(&ms_func);
		//------Test do a function every 1 ms
		
		if(ms_counter >= 1){
			changeLed();
			ms_counter = 0;
		}
		

		//------Test Software timer
		//timer.loop(); //Se reinicia el timer apenas termina de ejecutarse.
		//if(ms_counter >= 10000) timer.stop(); //a los 6 segundos elimina el timer

		//------Test GPIO
		//led = !btn();
	}

	return 0;
}
