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

public:
    ShiftRegister(const uint8_t pinLoad, const uint8_t pinEnable, const uint8_t pinData, const uint8_t pinClk) :
        _pinLoad(pinLoad), _pinEnable(pinEnable), _pinData(pinData), _pinClk(pinClk)
    {
        pinMode(_pinLoad,   OUTPUT);
        pinMode(_pinEnable, OUTPUT);
        pinMode(_pinData,    INPUT);
        pinMode(_pinClk,    OUTPUT);
    }

    uint8_t reading(void);

};

#endif