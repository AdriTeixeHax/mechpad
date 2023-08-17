#include "ShiftRegister.h"

constexpr uint8_t SHIFT_REGISTER_DELAY = 20;

uint8_t ShiftRegister::reading(void)
{
    static unsigned long elapsedTime = millis();
    
    if (millis() - elapsedTime > SHIFT_REGISTER_DELAY)
    {       
        // Writes a pulse to the load pin.
        digitalWrite(_pinLoad, LOW);
        //delayMicroseconds(1);
        digitalWrite(_pinLoad, HIGH);
        //delayMicroseconds(1);
        
        // Gets data from the Shift Register.
        digitalWrite(_pinClk, HIGH);
        digitalWrite(_pinEnable, LOW);
        uint8_t incoming = shiftIn(_pinData, _pinClk, LSBFIRST);
        digitalWrite(_pinEnable, HIGH);
        
        // Returns the read code.
        Serial.print("Pin States:\r\n");
        Serial.println(incoming, BIN);
        elapsedTime = millis();
        return incoming;
    }
}