/*
 * Serial.h
 *
 *  Created on: 9 jun. 2021
 *      Author: Damian Melamed
 */
#ifndef DR_H_HAL_SERIAL_H_
#define DR_H_HAL_SERIAL_H_

#include <System.h>
#include <Hardware/DR_UART.h>

class Serial {
   private:
    static uint8_t _uart_n, _tx_pin, _rx_pin, _tx_port, _rx_port;
    static uint16_t _baudRate;

   public:
    static void init(uint32_t baudrate, uint8_t uartN = UART1);
    static int32_t popRX(void);
    static void pushTX(uint8_t dato);
    static void print(const char* msj);
    static void print(uint32_t num);
    static void printBlocking(const char* msj);
    static void printBlocking(uint32_t num);
    static void println(const char* msj);
    static void println(uint32_t num);
    static char* read();
};

#endif