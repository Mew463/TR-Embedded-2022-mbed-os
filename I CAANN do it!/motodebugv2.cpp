// #include "mbed.h"
// #include "SerialCommunication.hpp"
// #include "motor.hpp"
// #include <cctype>
// #include "CANMsg.h"

// SerialCommunication Serial(USBTX, USBRX, 9600);

// char mycoolmessage[64];
// bool gimbly;
// int motorNum;
// int motorVal = 0;
// char firstChar;
// int feedbackMode = 0;

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

// int main(void) {

//     //Motor::rawSend(0x2FF,0,0,8000,0);
//     int motorVals[4] = {0,0,0,0};
//     int sendId = 0;
//     while (1) {
        
//         if (Serial.update(mycoolmessage)) {
//             firstChar = mycoolmessage[0];
//             switch(firstChar) {
//                 case 'a':
//                     motorNum = 1;
//                     break;
//                 case 'b':
//                     motorNum = 2;
//                     break;
//                 case 'c':
//                     motorNum = 3;
//                     break;
//                 case 'd':
//                     motorNum = 4;
//                     break;
//                 case 'e':
//                     motorNum = 5;
//                     break;
//                 case 'f':
//                     motorNum = 6;
//                     break;
//                 case 'g':
//                     motorNum = 7;
//                     break;
//                 case 'h':
//                     motorNum = 8;
//                     break;
//                 case '[':
//                     feedbackMode = 0;
//                     break;
//                 case ']':
//                     feedbackMode = 1;
//                     break;
//                 case ',':
//                     gimbly = false;
//                     printf("Gimbly mode deactivated\n");
//                     break;
//                 case '.':
//                     gimbly = true;
//                     printf("Gimbly mode activated\n");
//                     break;
//                 default:
//                     printf("didnt receiver letter\n");
//                     if (isNum(mycoolmessage)){ 
//                         motorVal = std::atoi(mycoolmessage);
//                         printf("Set motorVal to %d\n",motorVal);
//                     }
//                     break;
//             }
//             printf("Controlling Motor#%d\n",motorNum);
//             if(!gimbly){ //standard motors
//                 if(motorNum > 0 && motorNum <= 4){
//                     sendId = 0x200;
//                 }else if (motorNum > 4 && motorNum <= 8){
//                     sendId = 0x1FF;
//                 }
//             }else{ //those god-forsaken pieces of shit gimblies
//                 if(motorNum > 0 && motorNum <= 4){
//                     sendId = 0x1FF;
//                 }else if (motorNum > 4 && motorNum <= 8){
//                     sendId = 0x2FF;
//                 }
//             }
            
//             motorVals[(motorNum -1) % 4] = motorVal;
//             //printf("send[%d] = %d sendID: %x\n",(motorNum - 1) % 4, motorVals[(motorNum - 1) % 4], sendId);
//             printf("hfu98hy89qur0q3wjo0pjcho98ha\n");
//             if(feedbackMode){
//                 Motor::getFeedback();
//             }
//         }
//         Motor::rawSend(sendId,motorVals[0],motorVals[1],motorVals[2],motorVals[3]);
//         Motor::update();
//     }


// }