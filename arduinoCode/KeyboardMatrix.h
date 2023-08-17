#ifndef _KEYBOARDMATRIX__H_
#define _KEYBOARDMATRIX__H_

#include "Globals.hpp"
#include "ShiftRegister.h"

class PinArray
{
private:
    const uint8_t _pinCount;
    uint8_t* _pins;

public:
    explicit PinArray(const uint8_t pinCount, uint8_t* pins) : _pinCount(pinCount), _pins(pins) {}
    ~PinArray(void) { delete _pins; }

    uint8_t operator[](uint8_t i) { return _pins[i]; }
    uint8_t pinCount(void) { return _pinCount; }
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
    uint16_t operator[](uint8_t i) { return _keypresses[i]; }
};

class KeyboardMatrix
{
private:
    PinArray _rowPins;
    ShiftRegister _shiftRegister;

public:
    KeyboardMatrix(const PinArray& rowPins, uint8_t SRPinLoad, uint8_t SRPinEnable, uint8_t SRPinData, uint8_t SRPinCLK) :
        _rowPins(rowPins),
        _shiftRegister(SRPinLoad, SRPinEnable, SRPinData, SRPinCLK)
    {
        for (uint8_t i = 0; i < COL_COUNT; i++)
            pinMode(BASE_COL_PIN + i, INPUT);

        for (uint8_t i = 0; i < ROW_COUNT; i++)
            pinMode(BASE_ROW_PIN + i, OUTPUT);
    }

    KeyboardData keypress(void);
};

#endif