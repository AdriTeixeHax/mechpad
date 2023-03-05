#include <FastLED.h>

#define LED_PIN     6
#define LED_COUNT  29

CRGB leds[LED_COUNT];

int speed = 50;         // Change this value to adjust the speed of the rainbow effect
int length = 10;        // Starting value for the length of the rainbow effect
int hue = 0;            // Starting hue value

void setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(100);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void loop()
{
    length = map(250, 0, 1023, 1, LED_COUNT);  // Change the length of the rainbow effect based on the analog input
    speed = 3;
    EVERY_N_MILLISECONDS(20) {
        hue += speed;           // Change this value to adjust the speed at which the hue changes
        for (int i = 0; i < LED_COUNT; i++)
        {
            int pixelHue = map(i, 0, length, hue, hue + 170);  // Map the hue value based on the length of the rainbow effect
            leds[i] = CHSV(pixelHue % 256, 255, 255);
        }
        FastLED.show();
    }
}