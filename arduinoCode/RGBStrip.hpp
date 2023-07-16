#ifndef _RGBSTRIP__HPP_
#define _RGBSTRIP__HPP_

#include "Globals.hpp"
#include "ParamList.hpp"
#include "Effect.hpp"

class RGBStrip
{
private:
    const uint _pin;
    const uint _rowCount;
    const uint _colCount;
    const uint _LEDCount;
    CRGB*      _strip;
    ParamList<Effect*> _effectList;
    CirclingEffect     _startupEffect;
    RainbowEffect      _rainbowEffect;
    RainEffect         _rainEffect;
    RainEffect         _lavaEffect;

public:
    /* CONSTRUCTOR */
    RGBStrip(const uint pin, const uint rowCount, const uint colCount);

    /* DESTRUCTOR */
    ~RGBStrip(void) { delete _strip; _effectList.clear(); }

    /* GETTERS */
    RainbowEffect* getRainbowEffect(void) { return &_rainbowEffect; }

    /* FUNCTIONS */
    void effectState(MachineState state);
};

#endif