#ifndef _KEYBOARDMATRIX__H_
#define _KEYBOARDMATRIX__H_

#include "Globals.hpp"
#include "ShiftRegister.h"

struct PinArray
{
    const uint _pinCount;
    byte* _pins;

    explicit PinArray(const uint pinCount, byte* pins) : _pinCount(pinCount), _pins(pins) {}
    ~PinArray(void) { delete _pins; }

    byte operator[](uint i) { return _pins[i]; }
};

struct KeyboardReading
{
    uint _numElem;
    int* _keypresses;

    KeyboardReading(void) : _numElem(0), _keypresses(nullptr) {}
    ~KeyboardReading(void) { this->reset(); }
    void reset(void) { _numElem = 0; _keypresses = nullptr; }
};

class KeyboardMatrix
{
private:
    PinArray _colPins;
    ShiftRegister _shiftRegister;

public:
    KeyboardMatrix(const uint colPinCount, byte* colPins) :
        _colPins(colPinCount, colPins),
        _shiftRegister(SR_PIN_LOAD, SR_PIN_EN, SR_PIN_DATA, SR_PIN_CLK)
    {
        for (uint i = 0; i < _colPins._pinCount; i++)
        {
            pinMode(_colPins[i], OUTPUT);
            digitalWrite(_colPins[i], HIGH);
        }
    }

    KeyboardReading* keypress(void);

};

#endif