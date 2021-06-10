/*
 * PWM.h
 *
 *  Created on: 5 ene. 2021
 *      Author: Damian Melamed
 */


#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <System.h>
#include <HAL/HardwareTimer.h>
class HardwareTimer;

class PWM 
{
public:
    enum channels{CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4};
    PWM(HardwareTimer& timer, uint8_t chn, uint8_t port, uint8_t pin);
    void init();
    void setDutyCycle(uint8_t dc);

private:
    uint8_t _timerN, _port, _pin, _chn;
    uint16_t _maxCount;

};

#endif