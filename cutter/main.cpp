#include "mbed.h"
#include"ultrasonic.h"
#include "USBSerial.h"

USBSerial serial;
Serial pc(USBTX, USBRX);
DigitalOut blueLED(P1_18);
DigitalOut redLED(P1_19);
int previousDistance = 0;
void dist(int distance)
{
    //put code here to happen when the distance is changed
    printf("distance changed to %dmm\r\n", distance);
    printf("something to check");
    int dis = distance - previousDistance;
    if(dis<500 and dis>100){
        printf("distance in between 500 and 100");
    
        //printf("rotet motor in suchway that cutter goes close to weed");
        //MotorReverse();call it from main function and set value in such way that after cutting desired distance
        //it come back its old position
    
        }
    else if(dis>=600 and dis<100){
        printf("don't need to do anything");
        //MotorStop();call it from main function
        }
    else{} 
    previousDistance = distance;
    printf("updated previous distance", previousDistance);
}

    
ultrasonic mu(P2_12, P2_13, .1, 1, &dist);

int main() {
    pc.baud(115200);
   // motorTicker.attach_us(&motorTick, 10000);
    //LEDTicker.attach_us(&LEDTick, 200000);
    mu.startUpdates();//start mesuring the distance
    while(1) {
     dist(mu.getCurrentDistance());
     // akhan theke current distence ta nilo parameter hise
    wait(1);
    mu.checkDistance();//call checkDistance() as possible, as this is where
        printf("changed value");
        // distance are in inch
        //if(d1>d2 and d1<4){
          //  printf("motor toward the obstacle to cut the weeds")//motor used at the place of linear actuator
           // }
        //if(d2<d1 and d2>3.8){
          //  printf("otor toward the obstacle");
            }
       // wait(0.5);
        //blueLED = 0;
    }

