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
class PWM : protected HardwareTimer
{
public:
    PWM(uint8_t timer, uint16_t presc, uint16_t period, uint8_t port, uint8_t pin);
    void setDutyCycle(uint8_t dc);

private:

};

#endif