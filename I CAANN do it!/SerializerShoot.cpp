// #include "mbed.h"
// #include <iostream>
// #include <string>
// #include "motor.hpp"

// DigitalIn myButton(PC_13);
// DigitalOut led(D13);

// Motor SerializerPushyThing(8);

// bool Toggle;
// bool lastButtonVal = false;
// bool buttonVal = false;
// int main() {
//     while (1) {
//         motorDebug = 1;
//         buttonVal = !myButton.read();
//         if (buttonVal && !lastButtonVal) {
//             printf("button pushed\n");
//             Toggle = !Toggle;
//         }

//         if (Toggle) {
//             led = 1;
//             SerializerPushyThing.setDesiredValue(-550);
//             Motor::update(); 
//             osDelay(60);
//             SerializerPushyThing.setDesiredValue(550);
//             Motor::update(); 
//             osDelay(350);

//         }
//         else {
//             led = 0;
//             SerializerPushyThing.setDesiredValue(0);
//         }
        
//         Motor::update();   
        
//         lastButtonVal = buttonVal;
//     }

// }
