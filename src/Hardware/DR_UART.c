/*
 * DR_PLL.c
 *
 *  Created on: Dec 30, 2020
 *  Author: Damian Melamed
 */


/*!-----------INCLUDES PRIVADOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <Hardware/DR_UART.h>

#ifdef __cplusplus
extern "C" {
#endif

volatile struct buf_st rx1_str = { 0, 0, };
volatile struct buf_st tx1_str = { 0, 0, };
volatile uint8_t tx1_restart = 0;

volatile struct buf_st rx2_str = { 0, 0, };
volatile struct buf_st tx2_str = { 0, 0, };
volatile uint8_t tx2_restart = 0;

extern inline void UART_setBaudRate(uint8_t uart_n, uint16_t BR){
    if (uart_n == UART1)    USART1->BRR =BR; 
    else                    USART2->BRR =BR;
}

extern inline void UART_enable(uint8_t uart_n){
    if(uart_n == UART1)
        USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE; //Enable UART, RX and TX
    else
        USART2->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE; //Enable UART, RX and TX
}

extern inline void UART_enableInterrupts(uint8_t uart_n){
    if(uart_n == UART1){
        USART1->CR1 &= ~(USART_CR1_TCIE);
        USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;
    }
    else{
        USART1->CR1 &= ~(USART_CR1_TCIE);
        USART2->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;
    }
}

extern inline void UART_setParity(uint8_t uart_n, uint8_t parity){
    if(uart_n == UART1){
        USART1->CR1 &= ~(USART_CR1_PCE);
        if(parity == UART_PAR_NONE) return;
        USART1->CR1 |= USART_CR1_PCE;

        USART1->CR1 &= ~USART_CR1_PS;
        if(parity == UART_PAR_ODD) USART1->CR1 |= USART_CR1_PS;
    }
    else{
        USART2->CR1 &= ~(USART_CR1_PCE);
        if(parity == UART_PAR_NONE) return;
        USART2->CR1 |= USART_CR1_PCE;

        USART2->CR1 &= ~USART_CR1_PS;
        if(parity == UART_PAR_ODD) USART2->CR1 |= USART_CR1_PS;
    }
}

extern inline void UART_setLenght(uint8_t uart_n, uint8_t lenght){
    if(uart_n == UART1){
        USART1->CR1 &= ~(USART_CR1_PCE);
        if(lenght == UART_LEN_9BITS) USART1->CR1 |= USART_CR1_PCE;
    }
    else{
        USART2->CR1 &= ~(USART_CR1_PCE);
        if(lenght == UART_LEN_9BITS) USART2->CR1 |= USART_CR1_PCE;
    }
}

extern inline void UART_setStopBits(uint8_t uart_n, uint8_t stopBits){
    if(uart_n == UART1){
        USART1->CR2 &= ~USART_CR2_STOP;
        USART1->CR2 |= (stopBits << USART_CR2_STOP_Pos);
    }
    else{
        USART2->CR2 &= ~USART_CR2_STOP;
        USART2->CR2 |= (stopBits << USART_CR2_STOP_Pos);
    }
}


void UART_pushRX(uint8_t uart_n, uint8_t data){
    if(uart_n == UART1) {
        rx1_str.buf[rx1_str.in] = data;
        rx1_str.in++;

        if(rx1_str.in == BUF_SIZE) {
            rx1_str.in = 0;
        }
    }
    else{
        //copiar para UART 2
    }
}

int16_t UART_popTX(uint8_t uart_n){
    int32_t result = 0;
    if(uart_n == UART1) {
        if(tx1_str.in == tx1_str.out)
        result = -1;
        else {
            result = tx1_str.buf[tx1_str.out];
            tx1_str.buf[tx1_str.out] = 0;
            tx1_str.out++;

            if(tx1_str.out == BUF_SIZE) 
                tx1_str.out = 0;
        }
    }
    else{

    }
    return result;
}

void UART_forceTX(uint8_t uart_n, uint8_t data){
    if(uart_n == UART1){
        USART1->CR1 |= USART_CR1_TXEIE;
        USART1->DR = data;
        
    }
    else{
        USART2->DR = data;
        USART2->CR1 |= USART_CR1_TXEIE;
    }   
}

void USART1_IRQHandler(){
        volatile uint8_t IIR = USART1->SR;
        volatile int32_t dato;

        if(IIR & USART_SR_RXNE){
            USART1->SR &= ~USART_SR_RXNE;
            UART_pushRX(UART1, USART1->DR);

		}
		else if(IIR & USART_SR_TXE){
            USART1->SR &= ~USART_SR_TXE;
            dato = UART_popTX(UART1);

			if(dato != -1)
				UART_forceTX(UART1, dato);
			else {
				tx1_restart = 0;
				USART1->CR1 &= ~(USART_CR1_TXEIE);
			}
        }

	}
#ifdef __cplusplus
}
#endif