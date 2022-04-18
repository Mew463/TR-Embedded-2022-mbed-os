#include "mbed.h"
#include "../TR-mbed6/util/communications/SerialCommunication.hpp"

SerialCommunication Serial(USBTX, USBRX, 9600);

char mycoolmessage[64];

int main() {

  while (1) {
        
        if (Serial.update(mycoolmessage)) {
            printf("your new messsage: %s\n", mycoolmessage);

            if (Serial.toNum(mycoolmessage) != NULL) 
                printf("message as an int: %d\n", Serial.toNum(mycoolmessage));
            
        }

    }

}