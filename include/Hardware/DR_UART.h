/*
 * DR_UART.h
 *
 *  Created on: 3 ene. 2021
 *      Author: Damian Melamed
 */

#ifndef DR_H_HARDWARE_DR_UART_H_
#define DR_H_HARDWARE_DR_UART_H_

/*!-----------INCLUDES PUBLICOS-----------------------------------------------------------------------------*/
#include <System.h>
#include <Hardware/DR_PLL.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!-----------DEFINES Y MACROS PUBLCIAS---------------------------------------------------------------------*/
#define BUF_SIZE   256	     /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/

enum UART_Baudrate{baud_9600 = 7500, baud_115200 = 625};
enum UART_N{UART1, UART2};
enum UART_int{UART_INT_RXNE, UART_INT_TXE};
enum UART_len{UART_LEN_8BITS, UART_LEN_9BITS};
enum UART_PARITY{UART_PAR_NONE, UART_PAR_ODD, UART_PAR_EVEN};
enum UART_STOP{UART_STOP_1B, UART_STOP_0_5B, UART_STOP_2B, UART_STOP_1_5B};
/*!-----------TIPOS DE DATOS PUBLCIAS-----------------------------------------------------------------------*/
struct buf_st {
  unsigned int in;                                // Next In Index
  unsigned int out;                               // Next Out Index
  char buf [BUF_SIZE];                           // Buffer
};
/*!-----------VARIABLES GLOBALES PUBLICAS-------------------------------------------------------------------*/

extern volatile struct buf_st rx1_str;
extern volatile struct buf_st tx1_str;
extern volatile uint8_t tx1_restart;

/*!-----------FUNCIONES-------------------------------------------------------------------------------------*/
void UART_setBaudRate(uint8_t uart_n, uint16_t BR);
void UART_enable(uint8_t uart_n);
void UART_enableInterrupts(uint8_t uart_n);
void UART_setParity(uint8_t uart_n, uint8_t parity);
void UART_setLenght(uint8_t uart_n, uint8_t lenght);
void UART_setStopBits(uint8_t uart_n, uint8_t stopBits);

void UART_pushRX(uint8_t uart_n, uint8_t data);
int16_t UART_popTX(uint8_t uart_n);
void UART_forceTX(uint8_t uart_n, uint8_t data);


#ifdef __cplusplus
}
#endif

#endif /* DR_H_HARDWARE_DR_UART_H_ */
