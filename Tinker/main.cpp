#include "mbed.h"

int main()
{
    while (true)
    {
        printf("%d\n", us_ticker_read());
    }
}