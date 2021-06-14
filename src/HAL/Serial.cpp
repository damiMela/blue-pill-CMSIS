/*
 * Serial.h
 *
 *  Created on: 9 jun. 2021
 *      Author: Damian Melamed
 */
#include <HAL/Serial.h>
#include <HAL/AlternatePin.h>
#include <HAL/InputPin.h>
#include <Hardware/DR_PLL.h>
#include <cstdlib>
uint8_t Serial::_uart_n = 0;
uint8_t Serial::_tx_pin = 0;
uint8_t Serial::_rx_pin = 0;
uint8_t Serial::_tx_port = 0;
uint8_t Serial::_rx_port = 0;
uint16_t Serial::_baudRate = 0;

void Serial::init(uint32_t baudrate, uint8_t uartN) {
    _uart_n = uartN;
    if (_uart_n == UART1) {
        _tx_port = PORTA;
        _tx_pin = 9;
        _rx_port = PORTA;
        _rx_pin = 10;
        APB_Enable(APB2, USART1_APB);
    } else {
        _tx_port = PORTA;
        _tx_pin = 2;
        _rx_port = PORTA;
        _rx_pin = 3;
        APB_Enable(APB1, USART2_APB);
    }

    if (baudrate == 9600)
        _baudRate = baud_9600;
    else if (baudrate == 115200)
        _baudRate = baud_115200;
    else
        _baudRate = baud_9600;
    ;

    AlternatePin::paramInit(_tx_port, _tx_pin, AlternatePin::PUSH_PULL, MAX_VEL_50MHZ);
    InputPin::paramInit(_rx_port, _rx_pin, InputPin::FLOATING);

    //config UART
    UART_setBaudRate(_uart_n, _baudRate);
    UART_enableInterrupts(_uart_n);
    UART_setLenght(_uart_n, UART_LEN_8BITS);
    UART_setParity(_uart_n, UART_PAR_NONE);
    UART_setStopBits(_uart_n, UART_STOP_1B);

    //clean buffer
    tx1_str.in = 0;
    tx1_str.out = 0;
    tx1_restart = 0;
    rx1_str.in = 0;
    rx1_str.out = 0;

    if (_uart_n == UART1) NVIC_EnableIRQ(USART1_IRQn);
    if (_uart_n == UART2) NVIC_EnableIRQ(USART2_IRQn);
    UART_enable(_uart_n);
}

int32_t Serial::popRX() {
    int32_t ret = -1;
    if (rx1_str.in != rx1_str.out) {
        ret = rx1_str.buf[rx1_str.out];
        rx1_str.out++;
        rx1_str.out %= BUF_SIZE;
    }
    return ret;
}

void Serial::pushTX(uint8_t data) {
    if (!tx1_restart) {
        UART_forceTX(UART1, data);
        tx1_restart = 1;
    } else {
        tx1_str.buf[tx1_str.in] = data;
        tx1_str.in++;
        if (tx1_str.in == BUF_SIZE) tx1_str.in = 0;
    }
}

void Serial::print(const char* msj) {
    uint32_t i = 0;
    while (msj[i] > 0) {
        pushTX(msj[i]);
        i++;
    }
}

void Serial::print(uint32_t num) {
    uint8_t i = 0;
    char temp[16] = "";  //32bit number has 15 digits;
    while (num || (i <= 0)) {
        temp[i] = num % 10;
        num /= 10;
        i++;
    }
    while (i) {
        pushTX(temp[i - 1] + '0');
        i--;
    }
}

void Serial::printBlocking(const char* msj) {
    uint32_t i = 0;
    while (msj[i] != '\0') {
        USART1->DR = msj[i];
        while ((USART1->SR & USART_SR_TXE) == 0) continue;
        i++;
    }
}

void Serial::printBlocking(uint32_t num) {
    uint8_t digits = 0;

    uint32_t temp = num;
    while (temp != 0) {
        temp /= 10;
        digits++;
    }

    char* str = (char*)calloc(digits, sizeof(char));
    printBlocking(itoa(num, str, 10));
}

void Serial::println(uint32_t num) {
    print(num);
    pushTX('\n');
}

void Serial::println(const char* msj) {
    print(msj);
    pushTX('\n');
}