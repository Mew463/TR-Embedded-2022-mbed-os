#include "mbed.h"

DigitalOut led1(LED1);

Thread thread(osPriorityHigh);

void led2_thread()
{
    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(100);
    }
}

int main()
{
    thread.start(led2_thread);

    while (true) {
        printf("hello world!\n");
        ThisThread::sleep_for(500);
    }
}