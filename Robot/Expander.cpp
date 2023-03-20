#include "Expander.h"

Expander::Expander(byte address)
{
    _address = address;
    _board = Adafruit_PWMServoDriver(_address);
    _initialized = false;
}

void Expander::begin()
{
    if (!_initialized)
    {
        _board.begin();
        _initialized = true;
    }
}

void Expander::setDutyCycle(byte channel, byte duty_cycle)
{
    int pwm_on_point = map(duty_cycle, _MIN_DUTY_CYCLE, _MAX_DUTY_CYCLE, _MIN_PWM_ON, _MAX_PWM_ON);
    _board.setPWM(channel, _PWM_OFF_POINT, pwm_on_point);
}