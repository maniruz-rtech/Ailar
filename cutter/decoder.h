#ifndef SHIT
#define SHIT

#include "mbed.h"

class DECODER {   
public:
    DECODER (PinName channelA, PinName channelB);
    int read();     //return values of the encoder
    void reset();

private: 
    void decode();   // calaulate values of the encoder
    
    InterruptIn interruptA;   // channel A signal interruption
    InterruptIn interruptB;    //channel B signal interruption
    
    volatile int pulse;    //current encoder value
    
    int prevA;      //previous channel A value
    
};

#endif