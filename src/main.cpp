#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/SW_Timer.h>

//must be included last
#include <HAL/RHAL.h>

//Pin declaration
OutputPin Led(PORTC, 13);

//Variable declaration
uint32_t ms_counter = 0;

void ms_func(void){
	ms_counter++;
}

void changeLed(void){
	static uint8_t state = 0;
	Led << state;
	state = !state;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Inicialization
	Led.init();
	
	SW_Timer timer(1000, &changeLed);

	//Pin initialization
    Led << true;

	while(1){
		hal.do_every_1ms(&ms_func);
		timer.Reset(); //Se reinicia el timer apenas termina de ejecutarse.

		if(ms_counter >= 6000) timer.Stop(); //a los 6 segundos elimina el timer

	}
}
