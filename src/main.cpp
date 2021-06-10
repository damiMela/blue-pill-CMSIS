
#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/InputPin.h>
#include <HAL/SoftwareTimer.h>
#include <HAL/HardwareTimer.h>
#include <HAL/Serial.h>

//must be included last
#include <HAL/RHAL.h>


//Pin declaration
OutputPin led(PORTC, 13);
Serial serial(UART1, baud_9600);

//Variable declaration
volatile uint32_t ms_counter = 0;
volatile uint8_t state = 0;

void ms_func(void){	ms_counter++; }

void changeLed(void){
	led = state;
	state = !state;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Pin initialization
	led.init();
	led = 0;

	serial.init();

	//SoftwareTimer timer(1000, &changeLed);
	HardwareTimer HWtimer(_TIM2, 7200, 10000, &changeLed);
	
	

	while(1){
		hal.tick(&ms_func);
		//timer.loop();
	}
}



