#include "mbed.h"

class PWMMotor : PwmOut{
    public: 

    /**
    * @brief Construct a new PWM Output 
    * @param pin 
    * @param defaultVal from 0 - 0.99f
    */
    PWMMotor(PinName pin, double defaultVal) : PwmOut(pin) {
        period(.002f);
        write(defaultVal);
    }                                                                               

    /**
    * @brief Set PWM Output 
    * @param motorVal from 0 - 0.99f 
    */
    void set(double motorVal) {
        write(motorVal);
    }

};