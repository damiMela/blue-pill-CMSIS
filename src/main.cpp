#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/SoftwareTimer.h>

//must be included last
#include <HAL/RHAL.h>

//Pin declaration
OutputPin led(PORTC, 13);

//Variable declaration
uint32_t ms_counter = 0;

void ms_func(void){
	ms_counter++;
}

void changeLed(void){
	static uint8_t state = 0;
	led << state;
	state = !state;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Inicialization
	led.init();
	
	SoftwareTimer timer(500, &changeLed);

	//Pin initialization
    led << false;

	while(1){
		hal.tick(&ms_func);
		timer.reset(); //Se reinicia el timer apenas termina de ejecutarse.

		//if(ms_counter >= 6000) timer.stop(); //a los 6 segundos elimina el timer

	}

	return 0;
}
