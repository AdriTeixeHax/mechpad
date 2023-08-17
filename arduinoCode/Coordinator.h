#ifndef _COORDINATOR__H_
#define _COORDINATOR__H_

#include "RotaryEncoder.h"
#include "KeyboardMatrix.h"
#include "ShiftRegister.h"
#include "LCDScreen.hpp"
#include "RGBStrip.h"

class Coordinator
{
private:
    MachineState     _machineState;
    StripConfigState _stripConfigState;

    LCDScreen      _LCDScreen;
    RotaryEncoder  _rotaryEncoder;
    RGBStrip       _RGBStrip;
    KeyboardMatrix _keyboardMatrix;

public:
    Coordinator(void);

    void loop(void);
    void stateTransitions(void);
    void running(void);
    void stripConfig(void);

    static const uint16_t STARTUP_TIMEOUT = 2000;
};

#endif