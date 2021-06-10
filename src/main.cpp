
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
OutputPin led(PORTA, 6);
Serial serial(UART1, baud_9600);
HardwareTimer pwmTimer(HardwareTimer::TIMER3, 72, 100);

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
	led = 0;


	//SoftwareTimer timer(1000, &changeLed);
	//HWtimer.attachInterrupt(&changeLed);
	serial.init();
	pwmTimer.init();
	PWM pwm(pwmTimer, PWM::CHANNEL_1, PORTA, 6);	

	while(1){
		hal.tick(&ms_func);
		if((ms_counter >= 50) && !test){
			count++;
			ms_counter = 0;
		}
		if((ms_counter >= 50) && test){
			count--;
			ms_counter = 0;
		}

		if(count >= 50){
			test = 1;
		}
		if(count <= 0){
			test = 0;
		}
		//timer.loop();

		pwm.setDutyCycle(count);
	}
}



