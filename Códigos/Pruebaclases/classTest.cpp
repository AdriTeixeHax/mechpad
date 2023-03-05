#include "classTest.h"

bool Encoder::encoderSwitch(void) // Reads the encoder switch and performs an action based on the string that is passed to it.
{
    if (digitalRead(pinSW) == LOW)
    {
        // // Debug LEDs for testing.
        // digitalWrite(ENCODER_LED_TEST_1, HIGH);
        // digitalWrite(ENCODER_LED_TEST_2, HIGH);
        // delay(250);
        // digitalWrite(ENCODER_LED_TEST_1, LOW);
        // digitalWrite(ENCODER_LED_TEST_2, LOW);
        delay(DELAY_ENCODER_SW);
        return true;
    }
    else return false;
}

int Encoder::firstEncoderReading(void) // Assigns a first value to the encoder.
{
    lastState = digitalRead(pinA);
}

int Encoder::encoderReading(void)
{
    int clockwise = 0;

    currentState = digitalRead(pinA);

    if (currentState != lastState && currentState == 1) // If last and current state of the rotary encoder's pin A are different, then a pulse occurred.
    {													// React to only 1 state change to avoid double count.
        if (digitalRead(pinB) != currentState)
        {
            // Debug LEDs.
            // digitalWrite(ENCODER_LED_TEST_1, HIGH);
            // delay(150);
            // digitalWrite(ENCODER_LED_TEST_1, LOW);

            clockwise = 1;
        }
        else
        {
            // Debug LEDs.
            // digitalWrite(ENCODER_LED_TEST_2, HIGH);
            // delay(150);
            // digitalWrite(ENCODER_LED_TEST_2, LOW);

            clockwise = -1;
        }
    }
    lastState = currentState;

    return clockwise;
}