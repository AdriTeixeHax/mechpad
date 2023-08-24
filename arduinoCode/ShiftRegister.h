#ifndef _SHIFTREGISTER__H_
#define _SHIFTREGISTER__H_

#include "Globals.hpp"

class ShiftRegister
{
private:
    const uint8_t _pinLoad;
    const uint8_t _pinEnable;
    const uint8_t _pinData;
    const uint8_t _pinClk;

    uint8_t _lastValueByte;
    bool    _lastValueBin[8];

public:
    ShiftRegister(const uint8_t pinLoad, const uint8_t pinEnable, const uint8_t pinData, const uint8_t pinClk) :
        _pinLoad(pinLoad), _pinEnable(pinEnable), _pinData(pinData), _pinClk(pinClk), _lastValueByte(0), _lastValueBin({false})
    {
        pinMode(_pinLoad,   OUTPUT);
        pinMode(_pinEnable, OUTPUT);
        pinMode(_pinData,    INPUT);
        pinMode(_pinClk,    OUTPUT);
    }

    void reading(void);
    uint8_t getLastValueByte(void) { return _lastValueByte; }
    bool* getLastValueBin(void) { return _lastValueBin; }

    void clear(void) { _lastValueByte = 0; for (uint8_t i = 0; i < 8; i++) _lastValueBin[i] = false; }
    
    static const uint8_t MICROSECOND_DELAY = 5;
    static const uint8_t GENERAL_DELAY = 1;
};

#endif