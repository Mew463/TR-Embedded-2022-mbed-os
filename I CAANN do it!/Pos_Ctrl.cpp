#include "mbed.h"
#include "SerialCommunication.hpp"
#include "motor.hpp"


SerialCommunication Serial(USBTX, USBRX, 9600);

char mycoolmessage[64];

Motor myMotor(5);

int main(){
    motorDebug = 0;
    
    while(1){
        myMotor.setDesiredCurrent(1000);
        myMotor.update();
        printf("%d \n", myMotor.getSpeed());
        
    }
}