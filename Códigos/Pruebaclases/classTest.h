#ifndef CLASSTEST_H
#define CLASSTEST_H

#define DELAY_ENCODER_SW 250

#include <Arduino.h>

class Encoder
{
public:
	// Variables.
	int pinA, pinB, pinSW;
	int currentState, lastState;

public:
	// Methods.
	bool encoderSwitch(void);
	int  firstEncoderReading(void);
	int  encoderReading(void);
};

#endif
