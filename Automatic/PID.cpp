# include "PID.h"

PID::PID(int gainP, int gainI, int gainD): gainP(gainP), gainI(gainI), gainD(gainD)
{
    gainDivider = 256;
    iValue = 0;
    maxValue = errorMultiplier * 2500;
    errorMultiplier = 4096;
    prevError = 0;
    }

int PID::update(int setpoint, int feedback)//setpoint could be the speed or position of the motor here it is used for speed.
{
    int error = (setpoint - feedback);
    int pValue = gainP * error/gainDivider;
    iValue += gainI * errorMultiplier * error / gainDivider;
    int dValue = gainD * (error - prevError);
    
    if (iValue > maxValue)
    {
        iValue = maxValue; }
        else if (iValue < -maxValue)
        {
            iValue = -maxValue; }
    prevError = error;
    return pValue + iValue/ errorMultiplier + dValue;
    }