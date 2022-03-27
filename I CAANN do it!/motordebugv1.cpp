// #include "mbed.h"
// #include <iostream>
// #include <string>
// #include "motor.hpp"

// // Create a DigitalOutput object to toggle an LED whenever data is received.
// static DigitalOut led(LED1);

// // Create a BufferedSerial object with a default baud rate.
// using ThisThread::sleep_for;
// static BufferedSerial Serial(USBTX, USBRX, 9600);
// char comdata[64] = {};
// double numdata = 0;

// int canNum = 0;
// int value = 0;

// bool readSerial();

// int multiplier = 100;

// int main(void)
// {
//     motorDebug=1;
//     while (1)
//     {

//         if (readSerial())
//         {
//             if (comdata[0] == 'a')
//             {
//                 canNum = 1;
//                 value = 0;
//             }
//             else if (comdata[0] == 'b')
//             {
//                 canNum = 2;
//                 value = 0;
//             }
//             else if (comdata[0] == 'c')
//             {
//                 canNum = 3;
//                 value = 0;
//             }
//             else if (comdata[0] == 'd')
//             {
//                 canNum = 4;
//                 value = 0;
//             }
//             else if (comdata[0] == 'e')
//             {
//                 canNum = 5;
//                 value = 0;
//             }
//             else if (comdata[0] == 'f')
//             {
//                 canNum = 6;
//                 value = 0;
//             }
//             else if (comdata[0] == 'g')
//             {
//                 canNum = 7;
//                 value = 0;
//             }
//             else if (comdata[0] == 'h')
//             {
//                 canNum = 8;
//                 value = 0;
//             }
//             else
//             {
//                 if(std::isdigit(comdata[0])){
//                     value = std::stod(comdata);
//                 }else if(comdata[0] == '-'){
//                     multiplier = -multiplier;
//                 }else if(comdata[0] == 'n'){
//                     multiplier = 100;
//                 }else if(comdata[0] == 'm'){
//                     multiplier = 1000;
//                 }
//             }
//             printf("[%s]Editing Motor #%d\n",comdata, canNum);
//             printf("Setting a value of %d\n", value * multiplier);
//             Motor m(canNum);
//             m.setDesiredValue(value * multiplier);
//         }
//         Motor::update();
//     }
// }

// bool readSerial()
// {
//     if (Serial.readable())
//     {
//         for (int i = 0; i < sizeof(comdata); i++)
//             comdata[i] = 0;
//         ThisThread::sleep_for(100ms);
//         Serial.read(comdata, sizeof(comdata));
//         // numdata = std::stod(comdata);
//         return true;
//     }
//     else
//         return false;
// }
