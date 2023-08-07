#ifndef __ROTARYENCODER_HPP__
#define __ROTARYENCODER_HPP__

#include "Globals.hpp"

constexpr uint16_t MAX_SWITCH_TIME = 500;
constexpr uint16_t MIN_SWITCH_TIME = 50;
constexpr uint16_t STARTUP_TIMEOUT = 1000;

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
	const uint8_t _pinSwitch;
	// States for reading.
	bool _currentState;
	bool _lastState;
	bool _switchPressed;
	// Time the switch has been pressed for
	uint16_t _timePressed;
	// Resolution for some actions.
	uint16_t _resolution;
	uint16_t _maxResolution;
	// Reading data for the LCD
	EncoderData _lastReadData;

public:
	/* INITIALIZATION */
	RotaryEncoder(uint8_t pinA, uint8_t pinB, uint8_t pinSwitch);

	/* GETTERS */
	bool 		getSwitchPressed(void) { return _switchPressed; }
	uint16_t	getTimePressed  (void) { return _timePressed; }
	uint16_t	getResolution   (void) { return _resolution; }
	EncoderData getLastData	    (void) { return _lastReadData; }

	/* SETTERS */
	bool setMaxResolution(uint16_t maxResolution) { _maxResolution = maxResolution; return true;}
	bool incrCounter(int incr);
	void resetTimePressed(void) { _timePressed = 0; }
	void resetSwitchPressed(void) { _switchPressed = false; }

	/* FUNCTIONS */
	void reading(void);
	bool switchUpdate(void);
	bool switchLongPress(void) { return (this->getSwitchPressed() && this->getTimePressed() > MAX_SWITCH_TIME); }
	bool switchPress(void) { return (this->switchUpdate() && this->getTimePressed() > MIN_SWITCH_TIME && this->getTimePressed() < MAX_SWITCH_TIME); }
};

#endif