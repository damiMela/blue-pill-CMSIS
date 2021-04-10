#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/SW_Timer.h>

//must be included last
#include <HAL/RHAL.h>

uint32_t mscount = 0;


void ms_func(void){
	mscount++;
}

void setLed(void){

}


int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Pin Declaration
	OutputPin Led(PORTC, 13);

	SW_Timer timer1(1000, &setLed);

	//Pin initialization
    Led = true;

	while(1){
		hal.do_every_1ms(&ms_func);

		if(mscount > 6000) Led = true;
		if((mscount > 3000) && (mscount < 6000)) Led = false;

	}
}
