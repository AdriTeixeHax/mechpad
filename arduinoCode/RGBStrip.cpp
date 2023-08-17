#include "RGBStrip.h"

uint16_t LEDMatrix::getIndex(uint8_t x, uint8_t y) const
{
    if (y % 2 != 0) // Odd y no.
        return (y * _colCount + (_colCount - x - 1));
    else
        return (y * _colCount + x);
}

RGBStrip::RGBStrip(const uint8_t pin, const uint8_t rowCount, const uint8_t colCount) :
    _pin(pin),
    _LEDCount(rowCount * colCount),
    _strip(new CRGB[_LEDCount]),
    _effectList(10),
    _startupEffect("Startup Effect", _LEDCount, matrix, &_effectList),
    _rainbowEffect("Rainbow Effect", _LEDCount, &_effectList),
    _rainEffect("Rain Effect", _LEDCount, &_effectList),
    _lavaEffect("Lava Effect", _LEDCount, &_effectList),
    matrix(rowCount, colCount)
{
    switch(_pin)
    {
    case PWM_PINS[0]: FastLED.addLeds<WS2812B, PWM_PINS[0], GRB>(_strip, _LEDCount); break;
    case PWM_PINS[1]: FastLED.addLeds<WS2812B, PWM_PINS[1], GRB>(_strip, _LEDCount); break;
    case PWM_PINS[2]: FastLED.addLeds<WS2812B, PWM_PINS[2], GRB>(_strip, _LEDCount); break;
    case PWM_PINS[3]: FastLED.addLeds<WS2812B, PWM_PINS[3], GRB>(_strip, _LEDCount); break;
    case PWM_PINS[4]: FastLED.addLeds<WS2812B, PWM_PINS[4], GRB>(_strip, _LEDCount); break;
    case PWM_PINS[5]: FastLED.addLeds<WS2812B, PWM_PINS[5], GRB>(_strip, _LEDCount); break;
    case PWM_PINS[6]: FastLED.addLeds<WS2812B, PWM_PINS[6], GRB>(_strip, _LEDCount); break;
    }
}

void RGBStrip::effectState(MachineState state)
{
    switch (state)
    {
    case MachineState::startup:       _startupEffect.effectAction(_strip); break;
    case MachineState::running:       _rainbowEffect.effectAction(_strip); break;
    case MachineState::stripConfig:   _rainbowEffect.effectAction(_strip); break;
    case MachineState::encoderConfig: _rainbowEffect.effectAction(_strip); break;
    case MachineState::error:         _rainbowEffect.effectAction(_strip); break;
    default: break;        
    }
}