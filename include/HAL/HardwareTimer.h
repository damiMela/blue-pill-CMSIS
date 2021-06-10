#ifndef HAL_HARDWARETIMER_H
#define HAL_HARDWARETIMER_H

#include <System.h>
#include <HAL/PWM.h>

class HardwareTimer
{
public:
    enum Timers {TIMER1, TIMER2, TIMER3};
    HardwareTimer(uint8_t timer, uint16_t presc, uint16_t period);
    void attachInterrupt(void (*function)(void));
    void setCallbackFunction(void (*function)(void));
    void init(void);

protected:
    void startTimer(); 
    uint8_t _timerN;
    uint16_t _presc, _period;

private:
    friend class PWM;
};

#endif