#include "mbed.h"

AnalogIn input(A5);

float myfloat = 1;

int main()
{
    while (true)
    {
        int val = int(input.read() * 255);
        if (val != 0)
            printf("%d\n", val);
    }
}