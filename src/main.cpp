#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/SW_Timer.h>

//must be included last
#include <HAL/RHAL.h>

uint32_t mscount = 0;


OutputPin Led(PORTC, 13);

void ms_func(void){
	mscount++;
	if(mscount == 1000) Led<<false;
	if(mscount == 2000) Led<<true;
}

void setLed(void){

}


int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Pin Inicialization
	Led.init();

	SW_Timer timer1(1000, &setLed);

	//Pin initialization
    Led << true;

	while(1){
		hal.do_every_1ms(&ms_func);

		if(mscount > 6000) Led << true;
		if((mscount > 3000) && (mscount < 6000)) Led << false;

	}
}
