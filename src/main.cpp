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

void setLed(void){
	static uint8_t state = 0;
	Led << state;
	state = !state;
	SW_Timer timer1(1000, &setLed);
}


int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Inicialization
	Led.init();
	SW_Timer timer1(1000, &setLed);

	//Pin initialization
    Led << true;

	while(1){
		hal.do_every_1ms(&ms_func);

		if(ms_counter > 6000) Led << true;

	}
}
