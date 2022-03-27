#include "mbed.h"

#include "Button.cpp"

Button myButton(BUTTON1);
DigitalOut led(D13);

// main() runs in its own thread in thes OS
int main()
{
    while (true) {
        myButton.update();

        if (myButton.getToggle())  
            led = 1;
        else
            led = 0;

        if (myButton.getInitialPress())
            printf("you just pressed the button! \n");

        if (myButton.getIntialRelease())
            printf("you just released the button! \n");




    
    }
}

