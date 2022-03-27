#include "mbed.h"

class Button : DigitalIn {
    private: 
        bool buttonState; // True = Pressed, False = Releaseds
        bool lastButtonState = false;
        bool toggleState;
    public:
        Button(PinName Pin) : DigitalIn(Pin){};

        void update() {
            buttonState = !read();

            if (buttonState && !lastButtonState)
                toggleState = !toggleState;

            lastButtonState = buttonState;
        }

        bool getToggle() {
            return toggleState;
        }

        bool getInitialPress() {
            buttonState = !read();
            if (buttonState && !lastButtonState)
                return true;
            else
                return false;

            lastButtonState = buttonState;
        }

        bool getIntialRelease() {
            buttonState = !read();
            if (!buttonState && lastButtonState)
                return true;
            else
                return false;

            lastButtonState = buttonState;
        }
    
    

};