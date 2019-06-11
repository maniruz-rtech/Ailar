#include "mbed.h"
#include "decoder.h"
#include "Motor.h"
#include "PID.h"
#include "MotorSpeedControl.h"
#include "MotorPositionControl.h"

//#include "USBSerial.h"
#include "ultrasonic.h"

//USBSerial serial;
Serial pc(USBTX, USBRX);

DigitalOut blueLED(P2_8);
DigitalOut redLED(P4_28);
Ticker motorTicker;
Ticker LEDTicker;
MotorSpeedControl motor1(P2_3, P0_21, P0_20, P0_19, P0_18);
MotorSpeedControl motor2(P2_2, P0_15, P0_16, P2_7, P2_6);
//MotorPositionControl motor2(P2_2, P0_15, P0_16, P2_7, P2_6);
MotorSpeedControl motor3(P2_1, P0_24, P0_25, P0_26, P0_9);
MotorSpeedControl motor4(P2_0, P0_7, P0_6, P0_5, P0_4);

char buf[64];
int  SerialCount = 0;
int distance1 = 0;

bool shouldSendFeedback = false;

int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void LEDTick() {
    blueLED = !blueLED;  
    //shouldSendFeedback = true; 
}

void motorTick() {
    motor1.motorTick();
    motor2.motorTick();
    motor3.motorTick();
    motor4.motorTick();
}

void exractCommand (char *buffer) {
    char *cmd = strtok(buffer, ":");
    redLED =! redLED;
    
    if (strncmp(cmd, "s", 1) == 0) {
        shouldSendFeedback = true;
        
        motor1.SettingSpeed = atoi(strtok(NULL, ":"));
        //motor2.SettingSpeed = atoi(strtok(NULL, ":"));
        motor3.SettingSpeed = atoi(strtok(NULL, ":"));
        motor4.SettingSpeed = atoi(strtok(NULL, ":"));
    }/* else if (strncmp(cmd, "ps", 2) == 0) {
        shouldSendFeedback = true;
        
        motor2.SettingPosition = atoi(strtok(NULL, ":"));
        motor2.MaxSpeedSetting = atoi(strtok(NULL, ":"));
    }*/
}   

void dist(int distance) {
    pc.printf("distance %dmm\n", distance);
    
    distance1 = distance;
}

//ultrasonic nu(P1_24, P1_23, .1, 1, &dist);
ultrasonic mu(P2_12, P2_13, .1, 1, &dist);

int main() {
    pc.baud(115200);
    motorTicker.attach_us(&motorTick, 10000);
    LEDTicker.attach_us(&LEDTick, 200000);
    mu.startUpdates();//start mesuring the distance
    
    while(1) {
        //int d1 = dist(mu.getCurrentDistance());// akhan theke current distence ta nilo parameter hisebe
        //int d2 = dist(nu.getCurrentDistance());
        mu.checkDistance();//call checkDistance() as possible, as this is where
        //the class check if dist needs to be called.

        if (pc.readable()) {
            buf[SerialCount] = pc.getc();
            
            if (buf[SerialCount] == '\n') {
                exractCommand(buf);
                SerialCount = 0;
                memset(buf, 0, 64);
            } else {
               ++SerialCount;
            }          
        }
        
        int minDistance = 100;
        int maxDistance = 500;
        int minPosition = 0;
        int maxPosition = 5000;
        
        int forwardSpeed = 0;
        int rotationSpeed = map(distance1, 300, 2000, 10, 0);
        
        //rotationSpeed = 0;
        
        if (rotationSpeed > 10) {
            rotationSpeed = 10;
        } else if (rotationSpeed < 0) {
            rotationSpeed = 0;
        }
        
        motor1.SettingSpeed = forwardSpeed + rotationSpeed;
        motor2.SettingSpeed = forwardSpeed + rotationSpeed;
        motor3.SettingSpeed = forwardSpeed + rotationSpeed;
        motor4.SettingSpeed = forwardSpeed + rotationSpeed;
        
        /*if (distance1 < maxDistance and distance1 > minDistance){
            motor2.SettingPosition = map(distance1, minDistance, maxDistance, minPosition, maxPosition);
            motor2.MaxSpeedSetting = 10;
        } else if (distance1 >= 600 and distance1 < 100){
            motor2.SettingPosition = motor2.getPosition();
        }*/
        
        if (shouldSendFeedback) {
            shouldSendFeedback = false;
            pc.printf("s1:%d, s2:%d, s3:%d, s4:%d\n", motor1.getSpeed(), motor2.getSpeed(), motor3.getSpeed(), motor4.getSpeed());
        }
    }
}
