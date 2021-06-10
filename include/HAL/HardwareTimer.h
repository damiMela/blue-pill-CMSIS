#ifndef HAL_HARDWARETIMER_H
#define HAL_HARDWARETIMER_H

#include <System.h>

class HardwareTimer
{
public:
    enum Timers {TIMER1, TIMER2, TIMER3};
    HardwareTimer(uint8_t timer, uint16_t presc, uint16_t val, void (*function)(void)=nullptr);
    void init(void);
    void setCallbackFunction(void (*function)(void));

protected:
    void startTimer(); 
    uint8_t _timerN;
    uint16_t _presc, _period;
};

#endif