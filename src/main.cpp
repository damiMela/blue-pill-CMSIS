#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/RHAL.h>
uint32_t mscount = 0;
bool led_state = false;

void ms_func(void){
	mscount++;
	if(mscount == 1000){
		mscount = 0;
		led_state = !led_state;
	}
}

void loop_func(void){

}


int main()
{
	RHAL hal;	

    OutputPin Led(PORTC, 13);
    Led = false;

	while(1){
		hal.do_every_1ms(&ms_func);
		Led = led_state;

	}
}
