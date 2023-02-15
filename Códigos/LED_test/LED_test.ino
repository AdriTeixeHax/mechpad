#include            "FastLED.h"
#define LED_TYPE     WS2812
#define DATA_PIN     3
#define CLOCK_PIN    13
#define NUM_LEDS     29
#define COLOR_ORDER  GRB
#define BRIGHTNESS   25

void setup() 
{
  uint8_t gHue      = 0; // Used to cycle through rainbow.
  uint8_t moveSpeed = 6; // Higher value moves pixel faster.
  CRGB leds[NUM_LEDS];

  delay(300);

  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop()
{
  EVERY_N_MILLISECONDS(50)
  {
    gHue++;
  } // Slowly cycle through the rainbow.

  uint8_t fadeRate = 10; // Use lower value to give a fading tail.

  EVERY_N_MILLISECONDS(5) 
  {
    fadeToBlackBy(leds, NUM_LEDS, fadeRate);
  } // Fade out pixels.

  uint16_t pos = beat8(moveSpeed) % NUM_LEDS; // Module the position to be within NUM_LEDS
  leds[pos] = CHSV(gHue, 200, 255);

  FastLED.show(); // Display the pixels.
}