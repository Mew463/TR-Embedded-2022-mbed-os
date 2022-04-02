#include "mbed.h"
#include "motor.hpp"

int main(){
    motorDebug = 0;
    Motor motorrrrrr(1,STANDARD);
    Motor gimbalii(7,GIMBLY);
    gimbalii.setPositionPID(5, 0, 10);
    motorrrrrr.setSpeedPID(0.5, 0, 2);
    int val = 0;
    while(1){
        motorrrrrr.setDesiredSpeed(2000);
        gimbalii.setDesiredPos(val);
        Motor::update();
        printf("\t\tSpeed:%d\n",motorrrrrr.getSpeed());
        //Motor::rawSend(0x202, val, val, val, val);
        //Motor::rawSend(0x1FF, val, val, val, val);
        //Motor::rawSend(0x2FF, 0, 0, val, 0);
        //Motor::getFeedback();
        //printf("%d\n",Motor::staticAngle(10));
    }
}