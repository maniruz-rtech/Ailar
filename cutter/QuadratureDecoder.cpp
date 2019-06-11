#include "QuadratureDecoder.h"
QuadratureDecoder :: QuadratureDecoder(PinName channelA, PinName channelB)
        : interruptA(channelA), interruptB(channelB){
                
                pulses = 0;
                prevA = interruptA.read();
                
                interruptA.rise(this, &QuadratureDecoder::decode);
                interruptA.fall(this, &QuadratureDecoder::decode);
                interruptA.rise(this, &QuadratureDecoder::decode);
                interruptA.fall(this, &QuadratureDecoder::decode);
                }
int QuadratureDecoder :: read(){
    return pulses;
    }                
void QuadratureDecoder :: decode(){
        int currentA = interruptA.read();
        int currentB = interruptB.read();
        
        int direction = prevA ^ currentB;
        
        if(direction){
            pulses++;
            }
        else{
            pulses--;
            }
        
        prevA = currentA;
}