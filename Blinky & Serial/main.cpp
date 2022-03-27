
//Built in LED is PA_5 or LED1
//Button is PC_13 or BUTTON1
// Go to mbed-os/drivers/include/drivers/ for all the references

#include "mbed.h" 
#include <string> 

// Initialise the digital pin LED1 as an output
DigitalOut led(D13);
// Intialize button pin as an input
DigitalIn myButton(PC_13);

// Create a BufferedSerial object with a default baud rate.
static BufferedSerial Serial(USBTX, USBRX, 9600);
char comdata[32] = {0};

string Message = "Intializing!";

int main()
{
    printf("%s", Message.c_str());
    
    while (true) {
        
        if (!myButton.read()) {
            printf("Button Pressed!\n");
            led = 1;
            osDelay(250);
            led = 0;
            osDelay(250);
        }
        else {
            if (Serial.readable()) {
                Serial.read(comdata, sizeof(comdata)); 

                if (std::strcmp(comdata, "1"))    
                    led = 0;
                if (std::strcmp(comdata, "0"))
                    led = 1;

                // Use printf to return input
                printf("I got %s \n", comdata);
            }
        }
    }
}

