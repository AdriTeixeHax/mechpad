#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 29

#define STRIP_BRIGHTNESS 20

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    pinMode(A0, INPUT);
    
    strip.begin();                         // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();                          // Turns off all pixels.
    strip.setBrightness(STRIP_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()
{
    // // Fill along the length of the strip in various colors...
    // colorWipe(strip.Color(255,   0,   0), 50); // Red
    // colorWipe(strip.Color(  0, 255,   0), 50); // Green
    // colorWipe(strip.Color(  0,   0, 255), 50); // Blue

    // // Do a theater marquee effect in various colors...
    // theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
    // theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
    // theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

    rainbowEffect(10, 1, 255, 255, true, LED_COUNT, 10);             // Flowing rainbow cycle along the whole strip
    //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
// void colorWipe(uint32_t color, int wait) {
//     for(int i = 0; i < strip.numPixels(); i++) // For each pixel in strip...
//     {
//         strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
//         strip.show();                          //  Update strip to match
//         delay(wait);                           //  Pause for a moment
//     }
// }

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
// void theaterChase(uint32_t color, int wait) {
//     for(int a=0; a<10; a++) {  // Repeat 10 times...
//         for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
//         strip.clear();         //   Set all pixels in RAM to 0 (off)
//         // 'c' counts up from 'b' to end of strip in steps of 3...
//         for(int c=b; c<strip.numPixels(); c += 3) {
//             strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//         }
//         strip.show(); // Update strip with new contents
//         delay(wait);  // Pause for a moment
//         }
//     }
// }

// Rainbow cycle along whole strip. Delay time (in ms) between frames.
void rainbowEffect(int wait, uint16_t reps, uint8_t saturation,
    uint8_t brightness, bool gammify, uint16_t numLEDs)
{
    for(uint16_t firstPixelHue = 0; firstPixelHue < 65535; firstPixelHue += 256)
    {
        for (uint16_t i = 0; i < numLEDs; i++)
        {
            uint16_t hue = firstPixelHue + ((i * reps * 65535) / numLEDs);
            uint32_t color = strip.ColorHSV(hue, saturation, brightness);

            if (gammify)
            {
                color = strip.gamma32(color);
            }
            strip.setPixelColor(i, color);
        }
        strip.show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
    }
}

// void rainbow2(uint16_t first_hue, int8_t reps, uint8_t saturation,
//     uint8_t brightness, bool gammify, uint16_t numLEDs, uint8_t skip)
// {
//   for (uint16_t i = 0; i < numLEDs; i += skip)
//   {
//     uint16_t hue = first_hue + (i * reps * 65536) / numLEDs;
//     uint32_t color = ColorHSV(hue, saturation, brightness);
//     if (gammify) color = gamma32(color);
//     setPixelColor(i, color);
//   }
// }

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
// void theaterChaseRainbow(int wait) {
//     int firstPixelHue = 0;     // First pixel starts at red (hue 0)
//     for(int a=0; a<30; a++) {  // Repeat 30 times...
//         for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
//         strip.clear();         //   Set all pixels in RAM to 0 (off)
//         // 'c' counts up from 'b' to end of strip in increments of 3...
//         for(int c=b; c<strip.numPixels(); c += 3) {
//             // hue of pixel 'c' is offset by an amount to make one full
//             // revolution of the color wheel (range 65536) along the length
//             // of the strip (strip.numPixels() steps):
//             int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
//             uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
//             strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//         }
//         strip.show();                // Update strip with new contents
//         delay(wait);                 // Pause for a moment
//         firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
//         }
//     }
// }
