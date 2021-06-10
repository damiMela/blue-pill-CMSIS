/*
 * Serial.h
 *
 *  Created on: 9 jun. 2021
 *      Author: Damian Melamed
 */
#include "HAL/Serial.h"
#include "Hardware/DR_GPIO.h"
#include <Hardware/DR_PLL.h>

Serial::Serial(uint8_t uart_n, uint16_t baudRate){
    _uart_n = uart_n;
    _baudRate = baudRate;

    if(uart_n == UART1){
        tx_port = PORTA;
        tx_pin = 9;

        rx_port = PORTA;
        rx_pin = 10;
    }
}

void Serial::init(){
    if(_uart_n == UART1)  APB_Enable(APB2, USART1_APB);
    else                APB_Enable(APB1, USART2_APB);

    GPIO_setDir(tx_port, tx_pin, ALTERNATE);
    GPIO_setAltMode(tx_port, tx_pin, ALTERNATE_PUSHPULL);
    GPIO_setMaxOutputSpeed(tx_port, tx_pin, MAX_VEL_50MHZ);
    
    GPIO_setDir(rx_port, rx_pin, INPUT);
    GPIO_setInputMode(rx_port, rx_pin, INPUT_FLOATING);
    
    UART_setBaudRate(_uart_n, _baudRate);
	//UART_setLenght(_uart_n, UART_LEN_8BITS);
    //UART_setParity(_uart_n, UART_PAR_NONE);
    //UART_setStopBits(_uart_n, UART_STOP_1B);
    tx1_str.in = 0; tx1_str.out = 0; tx1_restart = 0;    
    rx1_str.in = 0; rx1_str.out = 0;    

    UART_enableInterrupts(_uart_n);
    if(_uart_n == UART1)    NVIC_EnableIRQ(USART1_IRQn);
    if(_uart_n == UART2)    NVIC_EnableIRQ(USART2_IRQn);
    UART_enable(_uart_n);

    
}

int32_t Serial::popRX(){
    int32_t ret = -1;
	if(rx1_str.in != rx1_str.out){
		ret = rx1_str.buf[rx1_str.out];
		rx1_str.out++; 	rx1_str.out%=BUF_SIZE;
	}
	return ret;
}

void Serial::pushTX(uint8_t data){
    if(!tx1_restart) {
		UART_forceTX(UART1, data);
		tx1_restart = 1;
	}
	else {
		tx1_str.buf[tx1_str.in] = data;
		tx1_str.in++;
		if(tx1_str.in == BUF_SIZE)  tx1_str.in = 0;
	}
}


void Serial::print(char* msj){
	uint32_t i = 0;
	while(msj[i] > 0){
		pushTX(msj[i]);
		i++;
	}
}

void Serial::println(char* msj){
    print(msj);
    pushTX('\n');
}