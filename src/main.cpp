#include <stdio.h>

#include "System.h"
#include <HAL/OutputPin.h>
#include <HAL/InputPin.h>
#include <HAL/SoftwareTimer.h>
#include <HAL/HardwareTimer.h>
#include <HAL/PWM.h>
#include <HAL/Serial.h>

//must be included last
#include <HAL/RHAL.h>

#include <Hardware/DR_Timer.h>
#include <Hardware/DR_PLL.h>


//Pin declaration
OutputPin led(PORTC, 13);
InputPin btn(PORTB, 10, InputPin::PULLUP);
Serial serial(UART1, baud_9600);
HardwareTimer pwmTimer(HardwareTimer::TIMER3, 72, 100);
HardwareTimer HWtimer(HardwareTimer::TIMER2, 7200, 10000);

//Variable declaration
volatile uint32_t ms_counter = 0;
volatile uint8_t state = 0;
volatile uint8_t test = 0;
uint8_t count = 0;

void ms_func(void){	
	ms_counter++; 
}

void changeLed(void){
	led = state;
	state = !state;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Pin initialization
	led.init();
	btn.init();
	HWtimer.init();
	serial.init();
	

	//SoftwareTimer timer(1000, &changeLed);
	HWtimer.attachInterrupt(&changeLed);
	
	PWM pwm(pwmTimer, PWM::CHANNEL_1, PORTA, 6);	

	while(1){
		//timer.loop();
		hal.tick(&ms_func);
		if((ms_counter >= 50)){
			if(!test) count++;
			if(test) count --;
			ms_counter = 0;
			char data[10] = "";
			sprintf(data, "%d", count);
			serial.println(data);
		}

		if(count >= 50) test = 1;
		if(count <= 0)test = 0;

		pwm.setDutyCycle(count);
	}
}



