/*
#include "mbed.h"
#include <iostream>
#include <string>
#include "motor.hpp"

Motor LeftFront(1);
Motor LeftBack(2);
Motor RightFront(3);
Motor RightBack(4);

Timer t;

Motor myMotors[] = {LeftFront, LeftBack, RightFront, RightBack};
int motorSize = sizeof(myMotors) / sizeof(myMotors[0]);

void setAll(int value);

void runLeftFront(int value) {
    LeftFront.setDesiredValue(value);
}

void runLeftBack(int value) {
    LeftBack.setDesiredValue(value);
}

void runRightFront(int value) {
    RightFront.setDesiredValue(-value);
}

void runRightBack(int value) {
    RightBack.setDesiredValue(-value);
}


int movevalue = 8000;

int main() {

    //motorDebug = 1;

        for(int i = 0; i < movevalue/100; i++) {
            setAll(i*100);
            Motor::update(); 
            osDelay(1);
        }


        osDelay(2000);

        setAll(-3000);
        Motor::update();
        
        osDelay(1000);

        setAll(0);
        Motor::update();

    while (1);

}

void setAll(int value) {
    for (int i = 0; i < motorSize; i++) {
        if (i > 1)
            myMotors[i].setDesiredValue(-value);
        else
            myMotors[i].setDesiredValue(value);
        Motor::update();
    }
}
*/