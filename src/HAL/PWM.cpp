#include <HAL/PWM.h>
#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_Timer.h>

PWM::PWM(HardwareTimer& timer, uint8_t chn, uint8_t port, uint8_t pin){
    _pin = pin;
    _port = port;
    _chn = chn;
    _timer = &timer;
}


void PWM::init(){
    _timer->init();
    GPIO_setDir(_port, _pin, ALTERNATE);
    GPIO_setAltMode(_port, _pin, ALTERNATE_PUSHPULL);
    GPIO_setMaxOutputSpeed(_port, _pin, MAX_VEL_50MHZ);

    //config
    TIM_chnEn(_timer->_timerN, _chn);
    TIM_setOutputMode(_timer->_timerN, _chn, PWM_MODE1);
    TIM_preloadEn(_timer->_timerN, _chn);
    TIM_setVal(_timer->_timerN, _chn, 0);


    //enable timer
    _timer->startTimer();
}

void PWM::setDutyCycle(uint8_t dc){
    dc = dc > 100 ? 100 : dc;
    TIM_setVal(_timer->_timerN, _chn, (_timer->_period/100)*dc);
}