#ifndef _EFFECT__HPP_
#define _EFFECT__HPP_

#include "Globals.hpp"
#include "ParamList.hpp"

#include <FastLED.h>

#define everySetMillis EVERY_N_MILLISECONDS

class Effect
{
protected:
    string  _name;
    uint   _LEDCount;
    byte   _brightness;
    byte   _speed;

    /* CONSTRUCTOR */
    Effect(string name, const uint LEDCount, ParamList<Effect*>* effectList) :
        _name(name), _LEDCount(LEDCount), _brightness(20), _speed(3)
    { effectList->addElem(this); }

public:
    /* DESTRUCTOR*/
    virtual ~Effect(void) { }

    /* FUNCTIONS */
    virtual void effectAction(CRGB* strip) = 0;
};

class CirclingEffect : public Effect
{
public:
    /* CONSTRUCTOR */
    CirclingEffect(string name, const uint LEDCount, ParamList<Effect*>* effectList) : Effect(name, LEDCount, effectList) { }

    /* FUNCTIONS */
    void effectAction(CRGB* strip) override;
};

class RainbowEffect : public Effect
{
private:
    byte _hue;
    uint _length;

public:
    /* CONSTRUCTOR */
    RainbowEffect(string name, const uint LEDCount, ParamList<Effect*>* effectList) :
        Effect(name, LEDCount, effectList), _hue(3), _length(3)
    { }

    /* FUNCTIONS */
    void effectAction(CRGB* strip) override;
};

class RainEffect : public Effect
{
public:
    /* CONSTRUCTOR */
    RainEffect(string name, const uint LEDCount, ParamList<Effect*>* effectList) : Effect(name, LEDCount, effectList) { }  

    /* FUNCTIONS */
    void effectAction(CRGB* strip) override;
};

#endif