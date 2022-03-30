#include "mbed.h"
#include "SerialCommunication.hpp"
#include "motor.hpp"

int main(){
    motorDebug = 0;
    while(1){
        int val = 8738;
        //Motor::rawSend(0x202, val, val, val, val);
        //Motor::rawSend(0x1FF, val, val, val, val);
        Motor::rawSend(0x2FF, 0, 0, val, 0);
        Motor::getFeedback();
        //printf("%d\n",Motor::staticAngle(10));
    }
}