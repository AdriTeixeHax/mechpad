#include <FastLED.h>
#define NUM_LEDS 29
#define LED_PIN 3
#define GLOBAL_BRIGHTNESS 20

CRGBArray<NUM_LEDS> leds;

void setup()
{
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
}

void loop(){ 
  static uint8_t hue = 0;
  for(int i = 0; i < NUM_LEDS; i++) {   
    // fade everything out
    //leds.fadeToBlackBy(40);

    // let's set an led value
    leds[i] = CHSV(hue++,255,255);

    leds(NUM_LEDS,NUM_LEDS-1) = leds(NUM_LEDS - 1 ,0);
    FastLED.delay(3);
  }
}
