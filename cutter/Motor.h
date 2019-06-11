#ifndef MOTOR_H
#define MOTOR_H 

#include"mbed.h"
class Motor{
    
    public:
         Motor(PinName pwmPin, PinName dir1Pin, PinName dir2Pin);
         void setPWM(int pwmValue);
    private:
    PwmOut pwm;
    DigitalOut dir1;
    DigitalOut dir2;
    };
#endif