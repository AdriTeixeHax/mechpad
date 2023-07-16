#ifndef __ROTARYENCODER_HPP__
#define __ROTARYENCODER_HPP__

#include "Globals.hpp"

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

	/* ERROR CHECKING */
	bool errorChecking(void) { if (this == nullptr) return true; else return false; }

	/* GETTERS */
	uint getPinA	 	 (void) { if (!errorChecking()) return _pinA; }
	uint getPinB	 	 (void) { if (!errorChecking()) return _pinB; }
	uint getPinSwitch	 (void) { if (!errorChecking()) return _pinSwitch; }
	bool getCurrentState (void) { if (!errorChecking()) return _currentState; }
	bool getLastState	 (void) { if (!errorChecking()) return _lastState; }
	bool getSwitchPressed(void) { if (!errorChecking()) return _switchPressed; }
	uint getTimePressed  (void) { if (!errorChecking()) return _timePressed; }
	uint getResolution	 (void) { if (!errorChecking()) return _resolution; }
	ReadingData getLastData(void) { if (!errorChecking()) return _lastReadData; }

	/* SETTERS */
	bool setMaxResolution(uint maxResolution) { _maxResolution = maxResolution; return true;}
	bool incrCounter(int incr);
	void resetTimePressed(void) { _timePressed = 0; }

	/* FUNCTIONS */
	void reading(void);
	bool switchUpdate(void);
};

#endif