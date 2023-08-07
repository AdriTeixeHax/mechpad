#ifndef _KEYBOARDMATRIX__H_
#define _KEYBOARDMATRIX__H_

#include "Globals.hpp"
#include "ShiftRegister.h"

struct PinArray
{
    const uint8_t _pinCount;
    uint8_t* _pins;

    explicit PinArray(const uint8_t pinCount, uint8_t* pins) : _pinCount(pinCount), _pins(pins) {}
    ~PinArray(void) { delete _pins; }

    uint8_t operator[](uint8_t i) { return _pins[i]; }
};

class KeyboardData
{
private:
    const uint16_t _maxElem;
    uint16_t  _numElem;
    uint16_t* _keypresses;

public:
    KeyboardData(void) : _maxElem(10), _numElem(0), _keypresses(new uint16_t[_maxElem]) {}
    ~KeyboardData(void) { this->reset(); }
    void reset(void) { _numElem = 0; _keypresses = nullptr; }
    void addElem(uint16_t elem) { if ((_numElem + 1) <= _maxElem) _keypresses[++_numElem] = elem; }
    uint16_t getNumElem(void) { return _numElem; }
    uint16_t operator[](int i) { return _keypresses[i]; }
};

class KeyboardMatrix
{
private:
    PinArray _colPins;
    ShiftRegister _shiftRegister;

public:
    KeyboardMatrix(const uint8_t colPinCount, uint8_t* colPins, const uint8_t SRPinLoad, const uint8_t SRPinEnable, const uint8_t SRPinData, const uint8_t SRPinCLK) :
        _colPins(colPinCount, colPins),
        _shiftRegister(SRPinLoad, SRPinEnable, SRPinData, SRPinCLK)
    {
        for (uint16_t i = 0; i < _colPins._pinCount; i++)
        {
            pinMode(_colPins[i], OUTPUT);
            digitalWrite(_colPins[i], HIGH);
        }
    }

    KeyboardData* keypress(void);

};

#endif