#ifndef __ROTARYENCODER_HPP__
#define __ROTARYENCODER_HPP__

#include <Arduino.h>

using uint = unsigned int;
using byte = unsigned char;

struct ReadingData
{
	bool _hasBeenRotated;
	bool _direction; // true == clockwise, false == anticlockwise.

	explicit ReadingData(bool hasBeenRotated, bool direction) : _hasBeenRotated(hasBeenRotated), _direction(direction) {}
	void reset(void) { this->_hasBeenRotated = false; }
};

class RotaryEncoder
{
private:
	// Encoder pins.
	uint _pinA;
	uint _pinB;
	uint _pinSwitch;
	// States for reading.
	bool _currentState;
	bool _lastState;
	bool _switchPressed;
	// Counter for various functions.
    uint _counter;
	// Resolution for some actions.
	uint _resolution;
	uint _maxResolution;
	// Switch delay.
	uint _delayTime;

public:
	/* CONSTRUCTOR */
	RotaryEncoder(uint pinA, uint pinB, uint pinSwitch);

	/* ERROR CHECKING */
	bool errorChecking(void) { if (this == nullptr) return true; else return false; }

	/* GETTERS */
	uint getPinA	 	 (void) { if (!errorChecking()) return this->_pinA; }
	uint getPinB	 	 (void) { if (!errorChecking()) return this->_pinB; }
	uint getPinSwitch	 (void) { if (!errorChecking()) return this->_pinSwitch; }
	bool getCurrentState (void) { if (!errorChecking()) return this->_currentState; }
	bool getLastState	 (void) { if (!errorChecking()) return this->_lastState; }
	bool getSwitchPressed(void) { if (!errorChecking()) return this->_switchPressed; }
	uint getCounter	  	 (void) { if (!errorChecking()) return this->_counter; }
	uint getResolution	 (void) { if (!errorChecking()) return this->_resolution; }
	uint getDelayTime 	 (void) { if (!errorChecking()) return this->_delayTime; }

	/* SETTERS */
	bool setMaxResolution(uint maxResolution) { this->_maxResolution = maxResolution; return true;}
	bool incrCounter(int incr);

	/* FUNCTIONS */
	ReadingData reading(void);
	bool switchUpdate(void);
};

#endif