#ifndef _EFFECT__H_
#define _EFFECT__H_

#include "Globals.hpp"
#include "ParamList.hpp"

#include <FastLED.h>

#define everySetMillis EVERY_N_MILLISECONDS

class LEDMatrix
{
private:
    const uint8_t _rowCount;
    const uint8_t _colCount;

public:
    LEDMatrix(const uint8_t rowCount, const uint8_t colCount) : _rowCount(rowCount), _colCount(colCount) {}

    uint16_t getIndex(uint8_t x, uint8_t y) const;

    uint8_t rowCount(void) const { return _rowCount; }
    uint8_t colCount(void) const { return _colCount; }
};

class Effect
{
protected:
    string   _name;
    uint16_t _LEDCount;
    uint8_t  _brightness;
    uint8_t  _speed;

    /* CONSTRUCTOR */
    Effect(string name, const uint16_t LEDCount, ParamList<Effect*>* effectList) :
        _name(name), _LEDCount(LEDCount), _brightness(20), _speed(2)
    { effectList->addElem(this); }

    Effect(string name, const uint16_t LEDCount, ParamList<Effect*>* effectList, uint8_t speed) :
        _name(name), _LEDCount(LEDCount), _brightness(20), _speed(speed)
    { effectList->addElem(this); }

public:
    /* DESTRUCTOR*/
    virtual ~Effect(void) { }

    /* FUNCTIONS */
    virtual void effectAction(CRGB* strip) = 0;
};

class CirclingEffect : public Effect
{
private:
    uint8_t _fadeSpeed;
    float   _frequency;
    uint8_t _amplitude;
    const LEDMatrix& _matrix;

public:
    /* CONSTRUCTOR */
    CirclingEffect(string name, const uint16_t LEDCount, const LEDMatrix& matrix, ParamList<Effect*>* effectList) :
        Effect(name, LEDCount, effectList, 100), _fadeSpeed(128), _frequency(1.5f), _amplitude(30), _matrix(matrix)
    { }

    /* FUNCTIONS */
    void effectAction(CRGB* strip);
};

class RainbowEffect : public Effect
{
private:
    uint8_t _hue = 0;
    uint8_t _length;

public:
    /* CONSTRUCTOR */
    RainbowEffect(string name, const uint16_t LEDCount, ParamList<Effect*>* effectList) :
        Effect(name, LEDCount, effectList), _length(20)
    { }

    /* GETTERS */
    uint8_t getBrightness(void) { return _brightness; }
    uint8_t getLength    (void) { return _length; }
    uint8_t getSpeed     (void) { return _speed; }

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
    RainEffect(string name, const uint16_t LEDCount, ParamList<Effect*>* effectList) : Effect(name, LEDCount, effectList) { }  

    /* FUNCTIONS */
    void effectAction(CRGB* strip) override;
};

#endif