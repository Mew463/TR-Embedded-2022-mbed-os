#include "mbed.h"
#include "stdlib.h"
#include <string.h>
#include "pwmmotor.cpp"
#include "SerialCommunication.hpp"

PWMMotor brushlessmotor(D13,0.5f);

// Create a BufferedSerial object with a default baud rate.
SerialCommunication Serial(USBTX, USBRX, 9600);
static char message[32];


int main()
{
    while (true) {

        if (Serial.update(message)) {
            brushlessmotor.set(atof(message)); //not actually sure whether this works << ples test
            printf("success");
        }
        
    }
}
