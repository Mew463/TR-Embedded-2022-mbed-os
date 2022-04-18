#include "mbed.h"
#include "stdlib.h"
#include "../TR-mbed6/util/motor/pwmmotor.cpp"
#include "../TR-mbed6/util/communications/SerialCommunication.hpp"

PWMMotor brushlessmotor(D12, 90);

// Create a BufferedSerial object with a default baud rate.
SerialCommunication Serial(USBTX, USBRX, 9600);
static char message[32];


int main()
{
    while (true) {

        if (Serial.update(message)) {
            brushlessmotor.set(Serial.toNum(message));
            printf("success\n");
        }
        
    }
}
