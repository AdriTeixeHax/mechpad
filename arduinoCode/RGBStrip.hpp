#ifndef _RGBSTRIP__HPP_
#define _RGBSTRIP__HPP_

#include "Globals.hpp"
#include <FastLED.h>

class Effect
{
    ParamList<byte> _data;

};

class RGBStrip
{
private:
    const uint _pin;
    const uint _rowCount;
    const uint _colCount;
    const uint _LEDCount;
    const byte _brightness;
    CRGB*      _strip;
    Effect _startupEffect;
    Effect _rainbowEffect;
    Effect _rainEffect;
    Effect _lavaEffect;
    ParamList<ParamList<Effect>*> _effects;

public:
    /* CONSTRUCTOR */
    RGBStrip(const uint pin, const uint rowCount, const uint colCount);

    /* DESTRUCTOR */
    ~RGBStrip(void) { delete _strip; _effects.clear(); }

    /* SETTERS */
    void increaseEffectSpeed(const int increment, StripConfigState state)
    {

    }

    /* EFFECTS */
    void effectStartup(void);
    void effectRainbow(void);
    void effectRain(void);
    void effectLava(void);
};

#endif