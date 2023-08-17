#ifndef _RGBSTRIP__H_
#define _RGBSTRIP__H_

#include "Globals.hpp"
#include "ParamList.hpp"
#include "Effect.h"

class RGBStrip
{
private:
    const uint8_t _pin;
    const uint8_t _LEDCount;
    CRGB*         _strip;

    ParamList<Effect*> _effectList;
    CirclingEffect     _startupEffect;
    RainbowEffect      _rainbowEffect;
    RainEffect         _rainEffect;
    RainEffect         _lavaEffect;
    
public:
    LEDMatrix matrix;

public:
    /* CONSTRUCTOR */
    RGBStrip(const uint8_t pin, const uint8_t rowCount, const uint8_t colCount);

    /* DESTRUCTOR */
    ~RGBStrip(void) { delete _strip; _effectList.clear(); }

    /* GETTERS */
    RainbowEffect* getRainbowEffect(void) { return &_rainbowEffect; }

    /* FUNCTIONS */
    void effectState(MachineState state);
    void reset(void) { FastLED.setBrightness(0); for (uint16_t i = 0; i < _LEDCount; i++) _strip[i] = CRGB::Black; FastLED.show();}
};

#endif