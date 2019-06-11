#include "MotorPositionControl.h"

MotorPositionControl::MotorPositionControl(PinName pwmPin, PinName dir1Pin, PinName dir2Pin, PinName channelA, PinName channelB)
    : motor(pwmPin, dir1Pin, dir2Pin), decoder(channelA, channelB), positionPID(50,0,0), speedPID(50000,0,0)
    {
    SettingPosition = 0;
    MaxSpeedSetting = 0;
    CurrentPosition = 0;
    PreviousPosition = 0;
    CurrentSpeed = 0;  
    }

int MotorPositionControl::getPosition() {
    return CurrentPosition;  
 }   

int MotorPositionControl::getPWM() {
    return motor.getPWM();  
 }   
 
int MotorPositionControl::getSpeed() {
    return CurrentSpeed;  
 } 
void MotorPositionControl::motorTick() {
    CurrentPosition = decoder.read();
    

    int SettingSpeed = positionPID.update(SettingPosition, CurrentPosition);
    
    if (SettingSpeed > 0 && SettingSpeed > MaxSpeedSetting)
      {
        SettingSpeed = MaxSpeedSetting;
        }
    else if (SettingSpeed < 0 && SettingSpeed < -MaxSpeedSetting)
      {
        SettingSpeed = -MaxSpeedSetting;
        }
        
    
    CurrentSpeed = CurrentPosition - PreviousPosition;
    PreviousPosition = CurrentPosition;
    
    
    int pwmValue = speedPID.update(SettingSpeed, CurrentSpeed) ;   
    int minpwmValue = 250;
    if (pwmValue > 0 && pwmValue < minpwmValue)
      {
       pwmValue = minpwmValue;
       }
    else if (pwmValue < 0 && pwmValue > -minpwmValue)
    {
       pwmValue = -minpwmValue;
       }
       motor.setPWM(pwmValue);
}



