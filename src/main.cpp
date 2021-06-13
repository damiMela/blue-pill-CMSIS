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
OutputPin led(PORTC, 13);

//Variable declaration

uint32_t res = 0;
extern "C"{
	volatile uint8_t irr = 0;
}

void ms_func(void){	

}

void sendVal(void){
	ADC_startConvertion(_ADC1);
	uint16_t val1, val2;
	val1 = res >> 16;
	val2 = res & 0xFFFF;
	Serial::print(val1);
	Serial::print("\t");
	Serial::println(val2);
	irr = 0;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//timer initialization
	Serial::init(9600);
	SoftwareTimer timer(100, &sendVal);
	led.init();

	//set adc pins to input push-pull (is done by setting input pulldown)
 	GPIO_setDir(PORTB, 1, INPUT);
	GPIO_setInputMode(PORTB, 1, INPUT_PULLDOWN);
	GPIO_setDir(PORTB, 0, INPUT);
	GPIO_setInputMode(PORTB, 0, INPUT_PULLDOWN);

	//enable clock for adc and dma peripherals
	APB_Enable(APB2, ADC1_APB);
	APB_Enable(APB2, ADC2_APB);
	APB_Enable(AHB, DMA1_APB);
	
	ADC_setConvSequence(_ADC2, 8, 0);
	ADC_setSamplingRate(_ADC2, 8, CYCLES_71_5);
	ADC_setConvSequence(_ADC1, 9, 0);
	ADC_setSamplingRate(_ADC1, 9, CYCLES_71_5);

    ADC_dualModeENable();
    ADC_activateBySW(_ADC1);
    ADC_activateBySW(_ADC2);

    ADC_DMAEnable(_ADC1);
    ADC_DMAEnable(_ADC2);

	ADC_contConvEnable(_ADC2);
	ADC_contConvEnable(_ADC1);

	ADC_on(_ADC1);
	ADC_on(_ADC2);

    DMA_setPeriphAddr(0, &(ADC1->DR));
    DMA_setMemAddr(0, &res);
    DMA_setDataN(0, 2);
    DMA_setCircularMode(0);
    DMA_incrementMemAddr(0);
    DMA_setMemSize(0, DMA_32_BITS);
    DMA_setPerihpSize(0, DMA_32_BITS);
    DMA_enable(0);

	while(1){
		hal.tick(&ms_func);
		timer.loop();


		if(irr){
			
		}
	}
}

extern "C"{
	void ADC1_2_IRQHandler(void){
		irr = 1;
		ADC1->SR &= ~ADC_SR_EOC;
	}
}