
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

//Variable declaration
volatile uint32_t ms_counter = 0;
volatile uint8_t state = 0;
volatile uint8_t test = 0;

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
	HardwareTimer HWtimer(HardwareTimer::TIMER2, 7200, 10000, &changeLed);
	HWtimer.init();
	//PWM pwm(HardwareTimer::TIMER3, 72, 100, PORTA, 6);
/*	
	APB_Enable(APB1,TIM3_APB);

	GPIO_setDir(PORTA, 6, ALTERNATE);
    GPIO_setAltMode(PORTA, 6, ALTERNATE_PUSHPULL);
    GPIO_setMaxOutputSpeed(PORTA, 6, MAX_VEL_50MHZ);

    TIM3->CCER |= TIM_CCER_CC1E;
	TIM3->CR1 |= TIM_CR1_ARPE;
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE;

	TIM3->PSC = 72;
	TIM3->ARR = 100;
	TIM3->CCR1 = 10;


	TIM3->EGR |= TIM_EGR_UG;
	TIM3->CR1 |= TIM_CR1_CEN;*/
	

	

	while(1){
		hal.tick(&ms_func);
		//timer.loop();
	}
}



