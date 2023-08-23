#ifndef _VIRTUALSWITCH__HPP_
#define _VIRTUALSWITCH__HPP_

#include "ParamList.hpp"

class VirtualSwitch
{
private:
    bool _state = false;

    bool _switchPressed = false;

    bool _timeFlag    = false;
    bool _readingFlag = false;

    // Time variables for debouncing and counting how much time since the switch was pressed.
    unsigned long _elapsedTime = 0;
    uint32_t      _timePressed = 0;

public:
    /* CONSTRUCTOR */
    VirtualSwitch(ParamList<VirtualSwitch*>* list) { list->addElem(this); }

	/* GETTERS */
	bool          getSwitchPressed(void) { return _switchPressed; }
    unsigned long getTimePressed  (void) { return _timePressed; }

    /* SETTERS */
    void activate          (void) { _state = true; }
    void deactivate        (void) { _state = false; }
    void resetSwitchPressed(void) { _switchPressed = false; }
    void resetTimePressed  (void) { _timePressed = 0; }

    /* FUNCTIONS */
    bool switchUpdate(void)
    {
        static unsigned long tempPressed = 0;
        // Stores the time the switch has been pressed.
        if (_state) // If the switch is pressed
        {
            if (!_timeFlag) // and the time flag is not active
            {
                _timePressed = 0; // resets the time the switch has been pressed for,
                tempPressed = millis(); // sets a temporary variable to millis() -to compare it later and know the time the switch has been pressed for-
                _timeFlag = true; // and activates the time flag so that the function doesn't repeat until the switch is released.
            }
            _timePressed = millis() - tempPressed; // Updates the time the switch has been pressed for.
        }
        else _timeFlag = false;
        
        // Reads and stores the state of the switch.
        if (_state != _readingFlag && millis() - _elapsedTime > PRESET_DELAY)
        {
            _readingFlag = !_readingFlag;

            if (_state) _switchPressed = true;
            else _switchPressed = false;

            _elapsedTime = millis();

            return true;
        }
        else return false;
    }

    bool switchPress(void)
    {
        return
        (
            this->switchUpdate()
            && 
            _timePressed > MIN_SWITCH_TIME
            && 
            _timePressed < MAX_SWITCH_TIME
        );
    }

    bool switchLongPress(void) { return (_switchPressed && _timePressed > MAX_SWITCH_TIME); }

    /* STATICS */
    static const uint16_t MAX_SWITCH_TIME = 500;
    static const uint8_t  MIN_SWITCH_TIME = 20;
    static const uint8_t  PRESET_DELAY    = 20;
};

#endif