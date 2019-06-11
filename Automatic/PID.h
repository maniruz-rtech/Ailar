#ifndef PID_H
#define PID_H

#include "mbed.h"

class PID {   
public:
    PID(int gainP, int gainI, int gainD);   

    int update(int setpoint, int feedback);
    void setgainP(int gainP);
    void setgainI(int gainI);
    void setgainD(int gainD);
    void resetI();
private: 

    int errorMultiplier;
    int iValue;
    int gainDivider;
    int gainP;
    int gainI;
    int gainD;
    int prevError;
    int maxValue;
    
};

#endif