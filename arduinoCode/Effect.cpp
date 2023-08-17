#include "Effect.h"

void CirclingEffect::effectAction(CRGB* strip)
{
    float centerX = _matrix.colCount() / 2.0f - 1;
    float centerY = _matrix.rowCount() / 2.0f - 1;
    if (_matrix.colCount() % 2 == 0) centerX += 0.5f;
    if (_matrix.rowCount() % 2 == 0) centerY += 0.5f;

    static uint8_t time = 10;
    static unsigned long elapsedTime = millis();

    Serial.println("Center X:");
    Serial.println(centerX);
    Serial.println("Center Y:");
    Serial.println(centerY);

    if (millis() - elapsedTime > _speed)
    {
        FastLED.setBrightness(_brightness);

        // Sets all LEDs to black.
        //for (uint16_t i = 0; i < _LEDCount; i++) strip[i] = CRGB::Black;
        fadeToBlackBy(strip, _LEDCount, _fadeSpeed);

        //strip[_matrix.getIndex(centerX, centerY)] = CRGB::Blue;

        for (uint8_t y = 0; y < _matrix.rowCount(); y++)
        {
            for (uint8_t x = 0; x < _matrix.colCount(); x++)
            {
                double distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                double angle    = time * _frequency - distance * 0.2;

                int value = static_cast<int>(_amplitude * sin(angle));

                // If the indices belong inside the circle, sets the LED color to blue.
                if (value >= -1 && value <= 1)
                    strip[_matrix.getIndex(x, y)] = CRGB::Blue;
            }
        }
        time = (time + 1) % 360;
        FastLED.show();
        elapsedTime = millis();
    }

    //fadeToBlackBy(strip, _LEDCount, 10);
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