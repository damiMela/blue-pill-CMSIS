#ifndef HARDWARETIMER_H
#define HARDWARETIMER_H

#include <Hardware/DR_Timer.h>

class HardwareTimer
{
public:
    HardwareTimer(uint8_t timer, uint16_t presc, uint16_t val, void (*function)(void));
    void start(void);

private:
    uint8_t _timerN;
    uint16_t _presc, _val;
};

#endif