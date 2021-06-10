#include <HAL/PWM.h>
#include <Hardware/DR_GPIO.h>
#include <Hardware/DR_Timer.h>

PWM::PWM(HardwareTimer& timer, uint8_t chn, uint8_t port, uint8_t pin){
    _pin = pin;
    _port = port;
    _chn = chn;
    _maxCount = timer._period;
    _timerN = timer._timerN;

    timer.init();
    GPIO_setDir(_port, _pin, ALTERNATE);
    GPIO_setAltMode(_port, _pin, ALTERNATE_PUSHPULL);
    GPIO_setMaxOutputSpeed(_port, _pin, MAX_VEL_50MHZ);

    //config
    TIM_chnEn(_timerN, 0);
    TIM_setOutputMode(_timerN, 0, PWM_MODE1);
    TIM_preloadEn(_timerN, 0);
    TIM_setVal(_timerN, 0, 0);


    //enable timer
    timer.startTimer();
}

void PWM::setDutyCycle(uint8_t dc){
    dc = dc > 100 ? 100 : dc;
    TIM_setVal(_timerN, 0, (_maxCount/100)*dc);
}