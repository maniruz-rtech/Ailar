#include "decoder.h"

DECODER::DECODER(PinName channelA, PinName channelB)
    : interruptA(channelA), interruptB(channelB) {     
        
        pulse = 0;
        prevA = interruptA.read();
        
        interruptA.rise(this, &DECODER::decode);
        interruptA.fall(this, &DECODER::decode);
        interruptB.rise(this, &DECODER::decode);
        interruptB.fall(this, &DECODER::decode);
}
        
int DECODER::read() {
    return pulse;
}

void DECODER::reset() {
    pulse = 0;
}
        
void DECODER::decode()  {
    
    int currentA = interruptA.read();
    int currentB = interruptB.read();
    
    int direction = prevA ^ currentB;
    
    if (direction) {
        pulse++;
    } else {
        pulse--;
    }
    
    prevA  = currentA;
}
    