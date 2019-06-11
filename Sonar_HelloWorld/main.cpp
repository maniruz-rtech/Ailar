#include "mbed.h"
#include "ultrasonic.h"
int previousDistance = 0;
 void dist(int distance)
{
    //put code here to execute when the distance has changed
    printf("Distance %d mm\r\n", distance);
    int diff = distance - previousDistance;
    if(diff<500 && diff>100){
        printf("distance in between 500 and 100");
        }
    else if(diff>=600 || diff<100){
        printf("don't need to do anything");
        //MotorStop();call it from main function
        }
    previousDistance = distance;
    printf("updated previous distance", previousDistance);
        
}

ultrasonic mu(P2_12, P2_13, .1, 1, &dist);    //Set the trigger pin to D8 and the echo pin to D9
                                        //have updates every .1 seconds and a timeout after 1
                                        //second, and call dist when the distance changes

int main()
{
    mu.startUpdates();//start measuring the distance
    while(1)
    {
        //Do something else here
        mu.checkDistance();     //call checkDistance() as much as possible, as this is where
                                //the class checks if dist needs to be called.
                  
        printf("%d\n", mu.getCurrentDistance());
                      
        wait(1);
    }
}
