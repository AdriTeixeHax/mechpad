#ifndef _EFFECT__HPP_
#define _EFFECT__HPP_

#include "Globals.hpp"
#include "ParamList.hpp"

#include <FastLED.h>

#define everySetMillis EVERY_N_MILLISECONDS

class Effect
{
protected:
    string _name;
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
    byte _length;

public:
    /* CONSTRUCTOR */
    RainbowEffect(string name, const uint LEDCount, ParamList<Effect*>* effectList) :
        Effect(name, LEDCount, effectList), _hue(3), _length(3)
    { }

    /* SETTERS */
    void incrementSpeed(const int incr)
    {
        if      (_speed + incr <= 0)   _speed = 0;
        else if (_speed + incr >= 255) _speed = 255;
        else     _speed += incr;
    }

    void incrementLength(const int incr)
    {
        if      (_length + incr <= 0)   _length = 0;
        else if (_length + incr >= 255) _length = 255;
        else     _length += incr;
    }

    void incrementBrightness(const int incr)
    {
        if      (_brightness + incr <= 0)   _brightness = 0;
        else if (_brightness + incr >= 255) _brightness = 255;
        else     _brightness += incr;
    }

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