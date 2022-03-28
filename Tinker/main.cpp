#include "mbed.h"

int main()
{
    while (true)
    {
        int x = -10040;
        int16_t y = (int16_t)x;
        printf("%d\t%d\n", x,y);
    }
}