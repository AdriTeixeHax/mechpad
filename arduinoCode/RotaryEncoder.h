#ifndef __ROTARYENCODER_HPP__
#define __ROTARYENCODER_HPP__

#include "Globals.hpp"

constexpr uint MAX_SWITCH_TIME = 500;
constexpr uint MIN_SWITCH_TIME = 50;
constexpr uint STARTUP_TIMEOUT = 1000;

struct ReadingData
{
	bool hasBeenRotated;
	bool direction; // true == clockwise, false == anticlockwise.
	uint counter;

	ReadingData(void) : hasBeenRotated(false), direction(false), counter(0) {}
	void reset(void) { hasBeenRotated = false; }
};

class RotaryEncoder
{
private:
	// Encoder pins.
	const uint _pinA;
	const uint _pinB;
	const uint _pinSwitch;
	// States for reading.
	bool _currentState;
	bool _lastState;
	bool _switchPressed;
	// Time the switch has been pressed for
	uint _timePressed;
	// Resolution for some actions.
	uint _resolution;
	uint _maxResolution;
	// Reading data for the LCD
	ReadingData _lastReadData;

public:
	/* INITIALIZATION */
	RotaryEncoder(uint pinA, uint pinB, uint pinSwitch);

	/* GETTERS */
	bool 		getSwitchPressed(void) { return _switchPressed; }
	uint 		getTimePressed  (void) { return _timePressed; }
	uint 		getResolution	(void) { return _resolution; }
	ReadingData getLastData		(void) { return _lastReadData; }

	/* SETTERS */
	bool setMaxResolution(uint maxResolution) { _maxResolution = maxResolution; return true;}
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