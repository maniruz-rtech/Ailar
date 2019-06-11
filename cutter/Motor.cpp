#include "Motor.h"


Motor::Motor(PinName pwmPin, PinName dir1Pin, PinName dir2Pin)
     : pwm(pwmPin), dir1(dir1Pin), dir2(dir2Pin) 
        {
         pwm.period_us(2500);//this 2500 is hight pwm value as arduino header it's set 255 here we can mange as we wish
         }
void Motor::setPWM(int pwmValue){
    if(pwmValue<0){
        dir1 = 1;
        dir2 = 0;
        pwmValue = -pwmValue;
        }
    else{
        dir1 = 0;
        dir2 = 1;
        }
    pwm.pulsewidth_us(pwmValue);
    }