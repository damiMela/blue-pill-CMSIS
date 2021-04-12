/*
 * DR_Timer1.c
 *
 *  Created on: 3 ene. 2021
 *      Author: usuario
 */

/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <Hardware/DR_Timer.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!-----------DEFINES Y MACROS PRIVADOS---------------------------------------------------------------------*/


//#define 	TIM1_UpdateInt_en()			(TIM_REG[timN]->DIER.Update_intEn = 1)
//#define	TIM1_CompareInt_en()		(TIM_REG[timN]->DIER.COM_intEn = 1)
//#define 	TIM1_CompareChn_int_en(c)	(TIM_REG[timN]->DIER.CC_intEN |= (1 << c))
/*!-----------TIPOS DE DATOS PRIVADOS-----------------------------------------------------------------------*/


/*!-----------VARIABLES GLOBALES PRIVADAS-------------------------------------------------------------------*/
TIM_TypeDef *const TIM_REG[] = {
		((TIM_TypeDef *)TIM1_BASE),
		((TIM_TypeDef *)TIM2_BASE),
		((TIM_TypeDef *)TIM3_BASE)
};


/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

/*!-----------FUNCIONES/macros-------------------------------------------------------------------------------------*/

///general
extern inline void TIM_setPeriod(uint8_t timN, uint16_t val){
	TIM_REG[timN]->ARR = val;
}

extern inline void TIM_setPLL(uint8_t timN, uint16_t val){
	TIM_REG[timN]->PSC = val;
}

extern inline void TIM_setCountMode(uint8_t timN, uint8_t mode){
	TIM_REG[timN]->CR1 &= ~TIM_CR1_DIR;
	if(mode == DOWN_COUNT) TIM_REG[timN]->CR1 |= TIM_CR1_DIR;
}

extern inline void TIM_autoReload_en(uint8_t timN){
	TIM_REG[timN]->CR1 |=  TIM_CR1_ARPE;
}

extern inline void TIM_counter_en(uint8_t timN){
	TIM_REG[timN]->CR1 |= TIM_CR1_CEN;
}

extern inline void TIM_URS_en(uint8_t timN){
	TIM_REG[timN]->CR1 |= TIM_CR1_URS;
}

extern inline void TIM_Interrupt_en(uint8_t timN){
	TIM_REG[timN]->DIER |= TIM_DIER_UIE;
}

extern inline void TIM_Interrupt_dis(uint8_t timN){
	TIM_REG[timN]->DIER &= ~TIM_DIER_UIE;

}

extern inline void TIM_update_config(uint8_t timN){
	TIM_REG[timN]->EGR |= TIM_EGR_UG;
}



/*
//for PWM

inline void TIM_setClockDiv(uint8_t timN, uint8_t val){
	TIM_REG[timN]->CR1 &= ~TIM_CR1_CKD;
	TIM_REG[timN]->CR1 |= (val << TIM_CR1_CKD_Pos);
}

inline void TIM_setActiveHigh(uint8_t timN, uint8_t chnl){
	TIM_REG[timN]->CCER &= TIM_CCER
	//TIM_REG[timN]->CCER &= (1 << (CCER_POLAR_BIT + 4*chnl));
}

inline void TIM_output_en(uint8_t timN, uint8_t chnl){
	TIM_REG[timN]->CCER &= (1 << (CCER_OUT_EN_BIT + 4*chnl));
}

inline void TIM_setVal(uint8_t timN, uint8_t chnl, uint16_t val){
	TIM_REG[timN]->CCR[chnl] = val;
}


//for encoder mode
inline void TIM_setSlaveMode(uint8_t timN, uint8_t val){
	TIM_REG[timN]->SMCR |= val;
}

inline void TIM_setInput_NInv(uint8_t timN, uint8_t chnl){
	TIM_REG[timN]->CCER &= (1 << (CCER_POLAR_BIT + 4*chnl));
}

inline uint16_t TIM_getCount(uint8_t timN, uint8_t chnl){
	return TIM_REG[timN]->CCR[chnl];
}

void TIM_setSel(uint8_t timN, uint8_t chn, uint8_t sel){
	switch(chn){
	case CHN1_MODE:		TIM_REG[timN]->CCMR1_OUT.chnA_sel = sel;	break;
	case CHN2_MODE:		TIM_REG[timN]->CCMR1_OUT.chnB_sel = sel;	break;
	case CHN3_MODE:		TIM_REG[timN]->CCMR2_OUT.chnA_sel = sel;	break;
	case CHN4_MODE:		TIM_REG[timN]->CCMR2_OUT.chnB_sel = sel;	break;
	}
}

void TIM_setOutputMode(uint8_t timN, uint8_t chn, uint8_t mode){
	switch(chn){
	case CHN1_MODE:		TIM_REG[timN]->CCMR1_OUT.chnA_mode = mode;	break;
	case CHN2_MODE:		TIM_REG[timN]->CCMR1_OUT.chnB_mode = mode;	break;
	case CHN3_MODE:		TIM_REG[timN]->CCMR2_OUT.chnA_mode = mode;	break;
	case CHN4_MODE:		TIM_REG[timN]->CCMR2_OUT.chnB_mode = mode;	break;
	}
}

void TIM_setInputPLL(uint8_t timN, uint8_t chn, uint8_t pll){
	switch(chn){
	case CHN1_MODE:		TIM_REG[timN]->CCMR1_IN.chnA_Input_PLL = pll;	break;
	case CHN2_MODE:		TIM_REG[timN]->CCMR1_IN.chnB_Input_PLL = pll;	break;
	case CHN3_MODE:		TIM_REG[timN]->CCMR2_IN.chnA_Input_PLL = pll;	break;
	case CHN4_MODE:		TIM_REG[timN]->CCMR2_IN.chnB_Input_PLL = pll;	break;
	}
}

void TIM_preloadEn(uint8_t timN, uint8_t chn){
	switch(chn){
	case CHN1_MODE:		TIM_REG[timN]->CCMR1_OUT.chnA_preLd_en = 1;	break;
	case CHN2_MODE:		TIM_REG[timN]->CCMR1_OUT.chnA_preLd_en = 1;	break;
	case CHN3_MODE:		TIM_REG[timN]->CCMR1_OUT.chnA_preLd_en = 1;	break;
	case CHN4_MODE:		TIM_REG[timN]->CCMR1_OUT.chnA_preLd_en = 1;	break;
	}

}*/



#ifdef __cplusplus
}
#endif
