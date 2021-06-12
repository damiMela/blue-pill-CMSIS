/*
 * DR_Timer1.h
 *
 *  Created on: 3 ene. 2021
 *      Author: usuario
 */

#ifndef DR_H_HARDWARE_DR_TIMER_H_
#define DR_H_HARDWARE_DR_TIMER_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <Hardware/DR_PLL.h>

#ifdef __cplusplus
extern "C" {
#endif

#define N_HARDWARE_TIMERS   3

/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/
enum timers_en{_TIM1, _TIM2, _TIM3};
enum count_mode{UP_COUNT, DOWN_COUNT};

enum ClockDiv_val{CLKDIV_1, CLKDIV_2, CLKDIV_4};

enum chn{CHN1, CHN2, CHN3, CHN4};
enum chn_sel{ OUTPUT_TIM, INPUT_TI2, INPUT_TI1, INPUT_TRC};
enum encoder_mode{ENC_MODE1 = 1, ENC_MODE2, ENC_MODE3};
enum PWM_mode{PWM_MODE1=6, PWM_MODE2};
enum slave_mode{SLAVE_DISABLED, SLAVE_ENC1, SLAVE_ENC2, SLAVE_ENC3, SLAVE_RST, SLAVE_GATE, SLAVE_TRIG, SLAVE_EXTCLK};
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/
/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/
//extern variables
TIM_TypeDef *const TIM_REG[] = {
		((TIM_TypeDef *)TIM1_BASE),
		((TIM_TypeDef *)TIM2_BASE),
		((TIM_TypeDef *)TIM3_BASE)
};

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
void TIM_setPeriod(uint8_t timN, uint16_t val);
void TIM_setPresc(uint8_t timN, uint16_t val);
void TIM_setCountMode(uint8_t timN, uint8_t mode);
void TIM_autoReload_en(uint8_t timN);
void TIM_counter_en(uint8_t timN);
void TIM_URS_en(uint8_t timN);
void TIM_Interrupt_en(uint8_t timN);
void TIM_Interrupt_dis(uint8_t timN);
void TIM_update_config(uint8_t timN);
static void TIM_rst_interrupt_flag(uint8_t timN){
 	TIM_REG[timN]->SR &= ~TIM_SR_UIF;
}

void TIM_chnEn(uint8_t timN, uint8_t chnl);
void TIM_preloadEn(uint8_t timN, uint8_t chn);
void TIM_setOutputMode(uint8_t timN, uint8_t chn, uint8_t mode);
void TIM_setVal(uint8_t timN, uint8_t chnl, uint16_t val);
/*
void TIM_output_en(uint8_t timN, uint8_t chnl);
void TIM_setSlaveMode(uint8_t timN, uint8_t val);
void TIM_setInput_NInv(uint8_t timN, uint8_t chnl);
uint16_t TIM_getCount(uint8_t timN, uint8_t chnl);

void TIM_setClockDiv(uint8_t timN, uint8_t val);
void TIM_setSel(uint8_t timN, uint8_t chn, uint8_t sel);
void TIM_setInputPLL(uint8_t timN, uint8_t chn, uint8_t pll);
*/
#ifdef __cplusplus
}
#endif

#endif /* DR_H_HARDWARE_DR_TIMER1_H_ */
