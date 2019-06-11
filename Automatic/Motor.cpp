#include "Motor.h"

Motor::Motor (PinName pwmPin, PinName dir1Pin, PinName dir2Pin)
   : pwm(pwmPin), dir1(dir1Pin), dir2(dir2Pin) {
       
       CurrentPWM = 0;
       period_us = 2500;  
       pwm.period_us(period_us); 
}

int Motor::getPWM()
    {
        return CurrentPWM;
        }

void Motor::setPWM(int pwmValue) {
    
    CurrentPWM = pwmValue;
    
    if (pwmValue < 0) {
        dir1 = 1;
        dir2 = 0;
        pwmValue = -pwmValue;
        
        } else {
        dir1 = 0;
        dir2 = 1;  
            }
    if (pwmValue > period_us)
        {
            pwmValue = period_us;
          }  
    pwm.pulsewidth_us(pwmValue);
    
} 