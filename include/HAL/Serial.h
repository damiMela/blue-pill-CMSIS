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

class Serial{
private:
	uint8_t _uart_n, tx_pin, rx_pin, tx_port, rx_port;
	uint16_t _baudRate;
	
public:
	Serial(uint8_t uart_n, uint16_t baudRate);
	void init();
	int32_t popRX(void);
	void pushTX(uint8_t dato);
	void print(char* msj);
	void println(char* msj);

};

#endif