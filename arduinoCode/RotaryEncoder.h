#ifndef __ROTARYENCODER_HPP__
#define __ROTARYENCODER_HPP__

#include "Globals.hpp"

struct EncoderData
{
	bool hasBeenRotated;
	bool direction; // true == clockwise, false == anticlockwise.
	uint16_t counter;

	EncoderData(void) : hasBeenRotated(false), direction(false), counter(0) {}
	void reset(void) { hasBeenRotated = false; }
};

class RotaryEncoder
{
private:
	// Encoder pins.
	const uint8_t _pinA;
	const uint8_t _pinB;
	// States for reading.
	bool _currentState;
	bool _lastState;
	// Resolution for some actions.
	uint16_t _resolution;
	uint16_t _maxResolution;
	// Reading data for the LCD
	EncoderData _lastReadData;

public:
	/* INITIALIZATION */
	RotaryEncoder(uint8_t pinA, uint8_t pinB);

	/* GETTERS */
	uint16_t	getResolution (void) { return _resolution; }
	EncoderData getLastData	  (void) { return _lastReadData; }

	/* SETTERS */
	bool setMaxResolution(uint16_t maxResolution) { _maxResolution = maxResolution; return true;}
	bool incrCounter(int incr);

	/* FUNCTIONS */
	void reading(void);
};

#endif