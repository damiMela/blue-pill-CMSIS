#include <HAL/PWM.h>
#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_Timer.h>

PWM::PWM(uint8_t timer, uint16_t presc, uint16_t period, uint8_t port, uint8_t pin) : HardwareTimer(timer, presc, period){
    GPIO_setDir(port, pin, ALTERNATE);
    GPIO_setAltMode(port, pin, ALTERNATE_PUSHPULL);
    GPIO_setMaxOutputSpeed(port, pin, MAX_VEL_50MHZ);

    //config
    TIM_chnEn(_timerN, 0);
    TIM_setOutputMode(_timerN, 0, PWM_MODE1);
    TIM_preloadEn(_timerN, 0);
    TIM_setVal(_timerN, 0, 0);


    //enable timer
    HardwareTimer::startTimer();
}

void PWM::setDutyCycle(uint8_t dc){
    dc = dc > 100 ? 100 : dc;
    TIM_setVal(_timerN, 0, (_period/100)*dc);
}