#ifndef Quadrature_DECODER_H
#define QUADRATURE_DECODER_H

#include "mbed.h"

class QuadratureDecoder {
    public:
        QuadratureDecoder(PinName channelA, PinName channelB);
        int read(); //RETURNS VALUE OF THE ENCODER
    private:
        void decode();
        InterruptIn interruptA; //channel A signal interrupt
        InterruptIn interruptB; //channel B signal interrupt
        
        volatile int pulses; //Current encoder value
        int prevA; //Current encoder value
    
                     };

#endif