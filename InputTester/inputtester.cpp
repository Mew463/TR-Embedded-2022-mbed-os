#include "mbed.h"

static BufferedSerial mySerial(PA_0, PA_1, 9600);

class InputTester{
    private:
        char message[32];
        int data[8] = {0,0,0,0,0,0,0,0};

    public: 

    InputTester() {}


    void update() {
        if (mySerial.readable()) {
            ThisThread::sleep_for(20ms);
            mySerial.read(message, sizeof(message));
            getData(message);

        }
    }

    void getData(char msg[]) {
        int i = 0;
        int z = 0;
        char numHolder[5];
        for (int y = 0; y < 8; y++) {
            while (msg[i] != ' ' || msg[i] != '\n') {
                numHolder[z] = msg[i];
                i++;
                z++;
            }

            data[y] = std::atoi(numHolder);
            printf("%d\n", std::atoi(numHolder));
            z = 0;

            for (int index = 0; index < sizeof(numHolder); index++)
                numHolder[index] = '\0';
        }
    }
};

