#include "mbed.h"
#include "SerialCommunication.hpp"
#include "motor.hpp"


SerialCommunication Serial(USBTX, USBRX, 9600);

char mycoolmessage[64];

Motor myMotor(5, 19);

int main(){
    motorDebug = 0;
    myMotor.setDesiredPos(0);
    int anglu = 0;
    while(1){
        
        if (Serial.update(mycoolmessage)){
            if(mycoolmessage[0] == 'z'){
                myMotor.zeroPos();
            }
            anglu = std::atoi(mycoolmessage);
            
            myMotor.setDesiredPos(anglu);
        }
        myMotor.update();
        printf("getangle: %d \n", myMotor.getAngle());
        //printf("%d\t%d\n",myMotor.getMultiTurnAngle(), std::atoi(mycoolmessage));
        
    }
}