#include "mbed.h"
#include "../TR-mbed6/util/communications/SerialCommunication.hpp"
#include "../TR-mbed6/util/motor/motor.hpp"
#include "../TR-mbed6/util/communications/canHandler.hpp"
#include "CANMsg.h"

CANHandler canPorts(PA_11,PA_12,PB_12,PB_13);

// Motor IDCanname | MotorType
Motor testMotor(5, CANHandler::CANBUS_1, GIMBLY);
Motor testMotor2(4, CANHandler::CANBUS_1, C620);

SerialCommunication Serial(USBTX, USBRX, 9600);
char mycoolmessage[64];




int main(void) {
    testMotor.setPositionOutputCap(8000);
    
    testMotor.setSpeedOutputCap(15000);
    testMotor.setSpeedIntegralCap(1000);

    testMotor2.setPositionPID(.20, 0, 10);
    testMotor2.setPositionOutputCap(1000);

    testMotor2.setSpeedPID(.5, .2, 7);
    testMotor2.setSpeedIntegralCap(400);
    testMotor2.setSpeedOutputCap(1000);

    Motor::setCANHandler(&canPorts);

    testMotor.zeroPos();

    int val = 0;
    
    while (1) {
        
        if (Serial.update(mycoolmessage)) {
            val = Serial.toNum(mycoolmessage);
            testMotor2.setDesiredPos(val);
            printf("sucessfullyl set\n");
        }
    
    }

}




bool checkJam(Motor *mymotor) {
    static int mycount = 0;

    if (mymotor->getData(TORQUE) > 300 && mymotor->getData(VELOCITY) == 0) 
        mycount++;
    else
        mycount = 0;
    
    if (mycount > 10)
        return true;
    else
        return false;
}