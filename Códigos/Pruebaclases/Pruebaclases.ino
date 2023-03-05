#include "classTest.h"
#include "HID-Project.h"

#define ENCODER_1_PIN_A  2
#define ENCODER_1_PIN_B  3
#define ENCODER_1_PIN_SW 8

#define ENCODER_LED_TEST_1 4
#define ENCODER_LED_TEST_2 5

Encoder rotaryEncoder1;

void setup()
{
	// HID initialization.
	Consumer.begin();

	// Encoder class pin definitions.
	rotaryEncoder1.pinSW = ENCODER_1_PIN_SW;
	rotaryEncoder1.pinA  = ENCODER_1_PIN_A;
	rotaryEncoder1.pinB  = ENCODER_1_PIN_B;

	// Encoder pins setup.
	pinMode(rotaryEncoder1.pinSW, INPUT_PULLUP);
	pinMode(rotaryEncoder1.pinA,  INPUT);
	pinMode(rotaryEncoder1.pinB,  INPUT);

	// Testing LEDs.
	pinMode(ENCODER_LED_TEST_1, OUTPUT);
	pinMode(ENCODER_LED_TEST_2, OUTPUT);
	digitalWrite(ENCODER_LED_TEST_1, LOW);
	digitalWrite(ENCODER_LED_TEST_2, LOW);

	// Do a first reading to setup a state for the encoder.
	rotaryEncoder1.firstEncoderReading();
}

void loop()
{
	int encoderReading = rotaryEncoder1.encoderReading();
	// Check if the button was pressed or if the encoder moved.
	switchAction(rotaryEncoder1.encoderSwitch(), MEDIA_PLAY_PAUSE);
	encoderAction(encoderReading, MEDIA_VOL_UP, MEDIA_VOL_DOWN);
}

// Actions regarding consumer or keypresses must be placed in the main file. Otherwise,
// there is a compilation error from the HID-Project library.
void encoderAction(int clockwise, ConsumerKeycode actionCW, ConsumerKeycode actionCCW)
{
	if (clockwise == 1)
		Consumer.write(actionCW);
	else if (clockwise == -1)
	{
		Consumer.write(actionCCW);
	}
}

void switchAction(bool pressed, ConsumerKeycode action)
{
	if (pressed) Consumer.write(action);
}