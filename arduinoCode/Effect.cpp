#include "Effect.hpp"

void CirclingEffect::effectAction(CRGB* strip)
{

}

void RainbowEffect::effectAction(CRGB* strip)
{
    everySetMillis(20)
    {
        FastLED.setBrightness(_brightness);

        _hue += _speed;
        for (int i = 0; i < _LEDCount; i++)
        {
            int pixelHue = map(i, 0, _length, _hue, _hue + 170);
            strip[i] = CHSV(pixelHue % 256, 255, 255);
        }
        FastLED.show();
    }
}

void RainEffect::effectAction(CRGB* strip)
{
    
}