#include <FastLED.h>
#define NUM_LEDS 29
#define LED_PIN 3
#define GLOBAL_BRIGHTNESS 20

CRGBArray<NUM_LEDS> leds;

void setup()
{

  pinMode(A0, INPUT);
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
}

void loop(){ 
  static uint8_t hue = 0;
  for(int i = 0; i < NUM_LEDS; i++)
  {   
    leds.fadeToBlackBy(0); // Fades an LED to black by the argument's value.

    leds[i] = CHSV(hue++,255,255); // Sets an led value

    leds(NUM_LEDS,NUM_LEDS-1) = leds(NUM_LEDS - 1 ,0);
    FastLED.delay(analogRead(A0));
  }
}
