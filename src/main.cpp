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


//Hardware declaration
Serial serial(UART1, baud_9600);

//Variable declaration
volatile uint32_t ms_counter = 0;
uint16_t res[4] = {0, 0, 0, 0};

void ms_func(void){	
	ms_counter++; 
}

void sendVal(void){
	ADC_startConvertion(_ADC1);

	char msg[10] = "";
	sprintf(msg, "%lu\t%lu\n", res[0], res[1]);
	serial.print(msg);
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//timer initialization
	serial.init();
	SoftwareTimer timer(100, &sendVal);

	//set adc pins to input push-pull (is done by setting input pulldown)
 	GPIO_setDir(PORTB, 1, INPUT);
	GPIO_setInputMode(PORTB, 1, INPUT_PULLDOWN);

	GPIO_setDir(PORTB, 0, INPUT);
	GPIO_setInputMode(PORTB, 0, INPUT_PULLDOWN);

	//enable clock for adc and dma peripherals
	APB_Enable(APB2, ADC1_APB);
	APB_Enable(APB2, ADC2_APB);
	APB_Enable(AHB, DMA1_APB);
	
	//set sampling rate for adc channels
	ADC_setSamplingRate(_ADC1, 9, CYCLES_71_5);
	ADC_setSamplingRate(_ADC1, 8, CYCLES_71_5);

	//set convertion order
	ADC_setConvSequence(_ADC1, 9, 0);
	ADC_setConvSequence(_ADC1, 8, 1);

	//set amount of convertions to be done
	ADC_setConvLenght(_ADC1, 2);

	ADC_ScanModeEnable(_ADC1);
	ADC_DMAEnable(_ADC1);

	//----------DMA
	//configure addr for peripheral and variable
	DMA_setPeriphAddr(0, (uint32_t)&ADC1->DR);
	DMA_setMemAddr(0, (uint32_t)res);

	DMA_setDataN(0, 2);	//amount of data to be read
	DMA_setCircularMode(0); //when it's done reading the N data, starts from 0
	DMA_incrementMemAddr(0);//load N data to N memory position 
	DMA_setMemSize(0, DMA_16_BITS);	//variable size
	DMA_setPerihpSize(0, DMA_16_BITS);//peripheral data size
	DMA_enable(0);

	ADC_activateBySW(_ADC1);
	ADC_on(_ADC1); //wake up peripheral
	for(uint32_t i = 0; i < 72000; i++); //wait for peripheral to respond. 1ms
	ADC_on(_ADC1);	//turn on perohperal
	for(uint32_t i = 0; i < 72000; i++); 
	ADC_caibrate(_ADC1);
	for(uint32_t i = 0; i < 144000; i++);//whait calibration. 2ms


	while(1){
		hal.tick(&ms_func);
		timer.loop();
	}
}
