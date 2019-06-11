#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor 
{
    public:
    Motor(PinName pmwPin, PinName dir1Pin, PinName dir2Pin);
    
   void setPWM(int pwmValue);
   int getPWM();

    private:
    PwmOut pwm;
    DigitalOut dir1;
    DigitalOut dir2;
    int period_us;
    int CurrentPWM;
};

#endif
    