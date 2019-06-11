#ifndef MOTORPOSITINCONTROL_H
#define MOTORPOSITINCONTROL_H

#include "mbed.h"
#include "Motor.h"
#include "decoder.h"
#include "PID.h"

class MotorPositionControl
{
public:
   MotorPositionControl(PinName pwmPin, PinName dir1Pin, PinName dir2Pin, PinName channelA, PinName channelB);
   void motorTick();
   int SettingPosition;
   int MaxSpeedSetting;
   int getPosition();
   int getPWM();
   int getSpeed();
private:
    int CurrentPosition;
    int PreviousPosition;
    int CurrentSpeed;
    Motor motor;
    DECODER decoder;
    PID positionPID;
    PID speedPID;
};
#endif