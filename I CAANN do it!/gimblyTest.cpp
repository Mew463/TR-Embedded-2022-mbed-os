// #include "mbed.h"
// #include "SerialCommunication.hpp"
// #include <cctype>
// #include "motor.hpp"

// SerialCommunication Serial(USBTX, USBRX, 9600);
// char mycoolmessage[64];

// bool isNum(char message[]) {
//     int i = 0;
//     if(message[0] == '-')
//         i = 1;
//     while(message[i] != '\0') {

//         if (!isdigit(message[i]))
//             return false;
//         i++;
//     }
//     return true;
// }

// int main(){
//     motorDebug = 0;
//     Motor motorrrrrr(1,STANDARD);
//     Motor gimbalii(7,GIMBLY);
//     gimbalii.setPositionPID(5, 0, 10);
//     int val = 0;
//     while(1){
//         if (Serial.update(mycoolmessage)) {
//             if (isNum(mycoolmessage)){ 
//                 val = std::atoi(mycoolmessage);
//                 printf("Set position to %d\n",val);
//             }
//         }
//         motorrrrrr.setDesiredCurrent(1000);
//         gimbalii.setDesiredPos(val);
//         Motor::update();
//         //Motor::rawSend(0x202, val, val, val, val);
//         //Motor::rawSend(0x1FF, val, val, val, val);
//         //Motor::rawSend(0x2FF, 0, 0, val, 0);
//         //Motor::getFeedback();
//         //printf("%d\n",Motor::staticAngle(10));
//     }
// }