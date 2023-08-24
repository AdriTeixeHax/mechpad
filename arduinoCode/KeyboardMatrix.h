#ifndef _KEYBOARDMATRIX__H_
#define _KEYBOARDMATRIX__H_

#include "Globals.hpp"
#include "ShiftRegister.h"

class KeyboardData
{
private:
    bool     _pressed;
    uint16_t _maxElem = 10;
    uint16_t _numElem;
    uint16_t _keypresses[10];

public:
    KeyboardData(void) : _pressed(false), _numElem(0), _keypresses({ 0 }) {}
    ~KeyboardData(void) { this->reset(); }
    void reset(void) { _pressed = false; for (uint16_t i = 0; i < _numElem; i++) _keypresses[i] = 0; _numElem = 0; }
    void addElem(uint16_t elem)
    {
        _pressed = true;
        if ((_numElem + 1) <= _maxElem)
        {
            _keypresses[_numElem] = elem;
            _numElem++;
        }
    }
    bool pressed(void) const { return _pressed; }
    uint16_t size(void) { return _numElem; }
    uint16_t operator[](uint8_t i) { return _keypresses[i]; }
};

class KeyboardMatrix
{
private:
    bool _hasShiftRegister;
    ShiftRegister _shiftRegister;
    KeyboardData  _lastData;

public:
    KeyboardMatrix(bool hasShiftRegister, uint8_t SRPinLoad = 0, uint8_t SRPinEnable = 0, uint8_t SRPinData = 0, uint8_t SRPinCLK = 0);

    void keypress(void);
    KeyboardData getLastData(void) const { return _lastData; }

};

#endif