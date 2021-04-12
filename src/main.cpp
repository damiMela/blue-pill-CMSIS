#include "System.h"

#include <HAL/RHAL.h>

//Pin declaration
OutputPin Led(PORTC, 13);
OutputPin my_pin(PORTC, 12);

//Variable declaration
uint32_t ms_counter = 0;
uint32_t us_counter = 0;


void ms_func(void){
	ms_counter++;
}

void changeLed(void){
	static uint8_t state = 0;
	Led << state;
	state = !state;
}

int main(){
	//RHAL definition. Must be At the top
	RHAL hal;	

	//Inicialization
	Led.init();
	my_pin.init();

	//Pin initialization
    Led << true;
	my_pin << true;

/*
	//Timer Cnfiguration
	APB_Enable(APB1, TIM2_APB);
	TIM_setPLL(_TIM2, 72);
	TIM_setPeriod(_TIM2, 100);
	TIM_autoReload_en(_TIM2);
	
	TIM_URS_en(_TIM2); //Only over/underflow generates interrupts. if not, UpdateGeneration (UG) interrupts the timer/	TIM2->DIER |= TIM_DIER_UIE; //Update interrupt enable
	TIM_Interrupt_en(_TIM2); //enable update interrupt
	TIM_update_config(_TIM2); //Update generation. After everything is set, configures the timer.
	TIM_counter_en(_TIM2);
*/
	NVIC_EnableIRQ(TIM2_IRQn);

	while(1){
		hal.do_every_1ms(&ms_func);
		Led << my_pin;


	}
}


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*	LOS HANDLERS TIENEN QUE ESTAR DEFINIDOS EN C  */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#ifdef __cplusplus
extern "C" {
#endif

void TIM2_IRQHandler(void){
	us_counter++;
	TIM2->SR &= ~TIM_SR_UIF;// clear status register "update interrupt flag"
}

#ifdef __cplusplus
}
#endif