#include "mbed.h"

DigitalOut led(D13);

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        led = 1;
        osDelay(500);
        led = 0;
        osDelay(500);
    }
}

