#include "RGBStrip.hpp"

RGBStrip::RGBStrip(const uint pin, const uint rowCount, const uint colCount) :
    _pin(pin),
    _rowCount(rowCount),
    _colCount(colCount),
    _brightness(20),
    _LEDCount(rowCount * colCount),
    _strip(new CRGB[_LEDCount])
{
    switch(_pin)
    {
    case PWM_PINS[0]:
        FastLED.addLeds<WS2812B, PWM_PINS[0], GRB>(_strip, _LEDCount);
        break;

    case PWM_PINS[1]:
        FastLED.addLeds<WS2812B, PWM_PINS[1], GRB>(_strip, _LEDCount);
        break;

    case PWM_PINS[2]:
        FastLED.addLeds<WS2812B, PWM_PINS[2], GRB>(_strip, _LEDCount);
        break;

    case PWM_PINS[3]:
        FastLED.addLeds<WS2812B, PWM_PINS[3], GRB>(_strip, _LEDCount);
        break;

    case PWM_PINS[4]:
        FastLED.addLeds<WS2812B, PWM_PINS[4], GRB>(_strip, _LEDCount);
        break;

    case PWM_PINS[5]:
        FastLED.addLeds<WS2812B, PWM_PINS[5], GRB>(_strip, _LEDCount);
        break;

    case PWM_PINS[6]:
        FastLED.addLeds<WS2812B, PWM_PINS[6], GRB>(_strip, _LEDCount);
        break;
    }

    _rainbowData.speed = 3;
    _rainbowData.length = 3;
}

void RGBStrip::effectRainbow(void)
{
    EVERY_N_MILLISECONDS(20)
    {
        FastLED.setBrightness(_brightness);

        _rainbowData.hue += _rainbowData.speed;
        for (int i = 0; i < _LEDCount; i++)
        {
            int pixelHue = map(i, 0, _rainbowData.length, _rainbowData.hue, _rainbowData.hue + 170);
            _strip[i] = CHSV(pixelHue % 256, 255, 255);
        }
        FastLED.show();
    }
}

void RGBStrip::effectRain(void)
{
    
}

void RGBStrip::effectLava(void)
{
    
}

void RGBStrip::effectStartup(void)
{
    FastLED.setBrightness(_brightness);


}