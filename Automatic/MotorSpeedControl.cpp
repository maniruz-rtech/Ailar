#include "MotorSpeedControl.h"

MotorSpeedControl::MotorSpeedControl(PinName pwmPin, PinName dir1Pin, PinName dir2Pin, PinName channelA, PinName channelB)
    : motor(pwmPin, dir1Pin, dir2Pin), decoder(channelA, channelB), speedPID(50000,0,0) {
    SettingSpeed = 0;
    currentSpeed = 0;  
}

int MotorSpeedControl::getPWM() {
    return motor.getPWM();  
 }   
 
int MotorSpeedControl::getSpeed() {
    return currentSpeed;  
}

void MotorSpeedControl::motorTick() {
    currentSpeed = decoder.read();
    decoder.reset();
    
    int pwmValue = speedPID.update(SettingSpeed, currentSpeed);
       
    int minpwmValue = 250;
    
    if (pwmValue > 0 && pwmValue < minpwmValue) {
       pwmValue = minpwmValue;
    } else if (pwmValue < 0 && pwmValue > -minpwmValue) {
       pwmValue = -minpwmValue;
    }
    
    motor.setPWM(pwmValue);
}



