#include "mbed.h"
#include "SerialCommunication.hpp"
#include "motor.hpp"


SerialCommunication Serial(USBTX, USBRX, 9600);

char mycoolmessage[64];

Motor myMotor(5, 19);

int main(){
    motorDebug = 0;
    myMotor.setDesiredPos(0);
    while(1){
        
        if (Serial.update(mycoolmessage)){
            if(mycoolmessage[0] == 'z'){
                myMotor.zeroPos();
            }
            
            myMotor.setDesiredPos(std::atoi(mycoolmessage));
        }
        myMotor.update();
        printf("%d\t%d\n",myMotor.getMultiTurnAngle(), std::atoi(mycoolmessage));
        
    }
}