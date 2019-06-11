#ifndef MOTORSPEEDCONTROL_H
#define MOTORSPEEDCONTROL_H

#include "mbed.h"
#include "Motor.h"
#include "decoder.h"
#include "PID.h"

class MotorSpeedControl
{
public:
   MotorSpeedControl(PinName pwmPin, PinName dir1Pin, PinName dir2Pin, PinName channelA, PinName channelB);
   int SettingSpeed;
   void motorTick();
   int getPWM();
   int getSpeed();
private:
    int currentSpeed;
    Motor motor;
    DECODER decoder;
    PID speedPID;
};
#endif