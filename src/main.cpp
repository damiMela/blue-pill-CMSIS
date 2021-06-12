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

#include <Hardware/DR_ADC.h>
#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_PLL.h>
#include <Hardware/DR_DMA.h>


//Pin declaration
OutputPin led(PORTC, 13);
//InputPin btn(PORTB, 1);
Serial serial(UART1, baud_9600);
HardwareTimer pwmTimer(HardwareTimer::TIMER3, 72, 100);
HardwareTimer HWtimer(HardwareTimer::TIMER2, 7200, 10000);

//Variable declaration
volatile uint32_t ms_counter = 0;
uint16_t res[2] = {0, 0};

void ms_func(void){	
	ms_counter++; 
}

void sendVal(void){
	char msg[10] = "";
	sprintf(msg, "%hu\t%hu\n", res[0], res[1]);
	serial.print(msg);
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Pin initialization
	serial.init();
	SoftwareTimer timer(100, &sendVal);

 	GPIO_setDir(PORTB, 1, INPUT);
	GPIO_setInputMode(PORTB, 1, INPUT_PULLDOWN);

	APB_Enable(APB2, ADC1_APB);
	APB_Enable(AHB, DMA1_APB);
	
	ADC_setSamplingRate(9, CYCLES_71_5);
	ADC_setSamplingRate(8, CYCLES_71_5);
	ADC_setConvSequence(9, 0);
	ADC_setConvSequence(8, 1);
	ADC_setConvLenght(2);

	ADC_ScanModeEnable();
	ADC_DMAEnable();

	DMA_setPeriphAddr(0, (uint32_t)&ADC1->DR);
	DMA_setMemAddr(0, (uint32_t)res);
	DMA_setDataN(0, 2);
	DMA_setCircularMode(0);
	DMA_incrementMemAddr(0);
	DMA_setMemSize(0, DMA_16_BITS);
	DMA_setPerihpSize(0, DMA_16_BITS);
	DMA_enable(0);

	ADC_contConvEnable();
	ADC_on();
	for(uint32_t i = 0; i < 72000; i++);
	ADC_on();	
	for(uint32_t i = 0; i < 72000; i++);
	ADC_caibrate();
	for(uint32_t i = 0; i < 144000; i++);


	while(1){
		hal.tick(&ms_func);
		timer.loop();
	}
}




