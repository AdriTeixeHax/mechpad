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
    uint16_t size(void) { return _numElem; }
    uint16_t operator[](uint8_t i) { return _keypresses[i]; }
    KeyboardData& operator= (const KeyboardData& kd)
    {
        _maxElem = kd._maxElem;
        _numElem = kd._numElem;
        for (uint16_t i = 0; i < kd._numElem; i++) _keypresses[i] = kd._keypresses[i];
    }
    bool pressed(void) const { return _pressed; }
};

class KeyboardMatrix
{
private:
    ShiftRegister _shiftRegister;
    KeyboardData  _lastData;

public:
    KeyboardMatrix(uint8_t SRPinLoad, uint8_t SRPinEnable, uint8_t SRPinData, uint8_t SRPinCLK) :
        _shiftRegister(SRPinLoad, SRPinEnable, SRPinData, SRPinCLK), _lastData()
    {
        for (uint8_t i = 0; i < COL_COUNT; i++)
            pinMode(BASE_COL_PIN + i, INPUT);

        for (uint8_t i = 0; i < ROW_COUNT; i++)
            pinMode(BASE_ROW_PIN + i, OUTPUT);
    }

    void keypress(void);
    KeyboardData getLastData(void) const { return _lastData; }

};

#endif