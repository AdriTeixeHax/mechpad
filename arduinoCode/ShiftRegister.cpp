#include "ShiftRegister.h"

void ShiftRegister::reading(void)
{
    this->clear();

    // Writes a pulse to the load pin.
    digitalWrite(_pinLoad, LOW);
    delayMicroseconds(MICROSECOND_DELAY);
    digitalWrite(_pinLoad, HIGH);
    delayMicroseconds(MICROSECOND_DELAY);
    
    // Gets data from the Shift Register.
    digitalWrite(_pinClk, HIGH);
    digitalWrite(_pinEnable, LOW);
    _lastValueByte = shiftIn(_pinData, _pinClk, LSBFIRST);
    digitalWrite(_pinEnable, HIGH);

    // Casts the value to a bool array
    for(uint8_t i = 0; i < 8; i++)
        _lastValueBin[7 - i] = (_lastValueByte >> i) & 1;
}