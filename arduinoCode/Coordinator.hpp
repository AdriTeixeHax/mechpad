#ifndef _COORDINATOR__HPP_
#define _COORDINATOR__HPP_

#include "RotaryEncoder.hpp"
// #include "KeyboardMatrix.hpp"
// #include "LCDScreen.hpp"
// #include "RGBStrip.hpp"

constexpr uint ENCODER_PIN_A  = 2;
constexpr uint ENCODER_PIN_B  = 3;
constexpr uint ENCODER_PIN_SW = 4;

class Coordinator
{
private:
    RotaryEncoder  _rotaryEncoder;
    // KeyboardMatrix _keyboardMatrix;
    // LCDScreen      _LCDScreen;
    // RGBStrip       _RGBStrip;

public:
    Coordinator(void) : _rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_SW) {}

    void loop(void);
};

#endif