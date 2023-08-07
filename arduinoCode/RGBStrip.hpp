#ifndef _RGBSTRIP__HPP_
#define _RGBSTRIP__HPP_

#include "Globals.hpp"
#include "ParamList.hpp"
#include "Effect.hpp"

class RGBStrip
{
private:
    const uint8_t _pin;
    const uint8_t _rowCount;
    const uint8_t _colCount;
    const uint8_t _LEDCount;
    CRGB*      _strip;
    ParamList<Effect*> _effectList;
    CirclingEffect     _startupEffect;
    RainbowEffect      _rainbowEffect;
    RainEffect         _rainEffect;
    RainEffect         _lavaEffect;

public:
    /* CONSTRUCTOR */
    RGBStrip(const uint8_t pin, const uint8_t rowCount, const uint8_t colCount);

    /* DESTRUCTOR */
    ~RGBStrip(void) { delete _strip; _effectList.clear(); }

    /* GETTERS */
    RainbowEffect* getRainbowEffect(void) { return &_rainbowEffect; }

    /* FUNCTIONS */
    void effectState(MachineState state);
};

#endif