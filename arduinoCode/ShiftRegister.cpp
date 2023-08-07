#include "ShiftRegister.h"

constexpr uint8_t SHIFT_REGISTER_DELAY = 20;

byte ShiftRegister::reading(void)
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