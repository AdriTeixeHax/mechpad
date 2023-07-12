#ifndef _RGBSTRIP__HPP_
#define _RGBSTRIP__HPP_

#include "Globals.hpp"
#include <FastLED.h>

struct EffectData
{ 
    uint length, speed, hue;
    void reset(void) { length = 0; speed = 0; hue = 0; }
};

enum class Effect { none, startup, rainbow, rain, lava };

class RGBStrip
{
private:
    const uint _pin;
    const uint _rowCount;
    const uint _colCount;
    const uint _LEDCount;
    const byte _brightness;
    CRGB*      _strip;
    EffectData _startupData = { 0 };
    EffectData _rainbowData = { 0 };
    EffectData _rainData    = { 0 };
    EffectData _lavaData    = { 0 };

public:
    /* CONSTRUCTOR */
    RGBStrip(const uint pin, const uint rowCount, const uint colCount);

    /* DESTRUCTOR */
    ~RGBStrip(void) { delete _strip; }

    /* SETTERS */
    void increaseEffectSpeed(const int increment)
    {
        switch()
    }

    /* EFFECTS */
    void effectRainbow(void);
    void effectRain(void);
    void effectLava(void);
    void effectStartup(void);
};

#endif