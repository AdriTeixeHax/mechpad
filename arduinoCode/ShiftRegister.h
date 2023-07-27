#ifndef _SHIFTREGISTER__H_
#define _SHIFTREGISTER__H_

#include "Globals.hpp"

constexpr uint SHIFT_REGISTER_DELAY = 20;

class ShiftRegister
{
private:
    const uint _pinLoad;
    const uint _pinEnable;
    const uint _pinData;
    const uint _pinClk;

public:
    ShiftRegister(const uint pinLoad, const uint pinEnable, const uint pinData, const uint pinClk) :
        _pinLoad(pinLoad), _pinEnable(pinEnable), _pinData(pinData), _pinClk(pinClk)
    {
        pinMode(_pinLoad,   OUTPUT);
        pinMode(_pinEnable, OUTPUT);
        pinMode(_pinData,    INPUT);
        pinMode(_pinClk,    OUTPUT);
    }

    byte reading(void)
    {
        static unsigned long elapsedTime = millis();
        
        if (millis() - elapsedTime > SHIFT_REGISTER_DELAY)
        {       
            // Writes a pulse to the load pin.
            digitalWrite(_pinLoad, LOW);
            delayMicroseconds(5);
            digitalWrite(_pinLoad, HIGH);
            delayMicroseconds(5);
            
            // Gets data from the Shift Register.
            digitalWrite(_pinClk, HIGH);
            digitalWrite(_pinEnable, LOW);
            byte incoming = shiftIn(_pinData, _pinClk, LSBFIRST);
            digitalWrite(_pinEnable, HIGH);
            
            // Returns the read code.
            Serial.print("Pin States:\r\n");
            Serial.println(incoming, BIN);
            elapsedTime = millis();
            return incoming;
        }
    }
};

#endif