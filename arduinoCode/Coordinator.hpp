#ifndef _COORDINATOR__HPP_
#define _COORDINATOR__HPP_

#include "RotaryEncoder.h"
#include "KeyboardMatrix.h"
#include "ShiftRegister.h"
#include "LCDScreen.hpp"
#include "RGBStrip.hpp"

struct StateFlags
{
    bool _startup       = false;
    bool _running       = false;
    bool _stripConfig   = false;
    bool _encoderConfig = false;
    bool _error         = false;

    void reset(void)
    {
        _startup       = false;
        _running       = false;
        _stripConfig   = false;
        _encoderConfig = false;
        _error         = false;
    }

    void resetExcept(MachineState currentState)
    {
        this->reset();
        switch(currentState)
        {
        case MachineState::startup:
            _startup = true;
            break;

        case MachineState::running:
            _running = true;
            break;

        case MachineState::stripConfig:
            _stripConfig = true;
            break;

        case MachineState::encoderConfig:
            _encoderConfig = true;
            break;

        case MachineState::error:
            _error = true;
            break;
        }
    }
};

class Coordinator
{
private:
    MachineState     _machineState;
    StateFlags       _stateFlags;
    StripConfigState _stripConfigState;

    LCDScreen      _LCDScreen;
    RotaryEncoder  _rotaryEncoder;
    RGBStrip       _RGBStrip;
    //KeyboardMatrix _keyboardMatrix;

public:
    Coordinator(void);

    void loop(void);
};

#endif