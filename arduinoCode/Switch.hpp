#ifndef _SWITCH__HPP_
#define _SWITCH__HPP_

class Switch
{
private:
    // Reading pin
    const uint8_t _pin;

    bool _switchPressed = false;

    bool _timeFlag    = false;
    bool _readingFlag = false;

    // Time variables for debouncing and counting how much time since the switch was pressed.
    unsigned long _elapsedTime = 0;
    unsigned long _timePressed = 0;

public:
    /* CONSTRUCTOR */
    Switch(void) = delete;
    Switch(const uint8_t pin) : _pin(pin) {}

	/* GETTERS */
	bool          getSwitchPressed(void) { return _switchPressed; }
    unsigned long getTimePressed  (void) { return _timePressed; }

    /* SETTERS */
    void resetSwitchPressed(void) { _switchPressed = false; }
    void resetTimePressed  (void) { _timePressed = 0; }

    /* FUNCTIONS */
    bool switchUpdate(void)
    {
        // Stores the time the switch has been pressed.
        if (!digitalRead(_pin))
        {
            if (!_timeFlag)
            {
                _timePressed = millis();
                _timeFlag = !_timeFlag;
            }
            _timePressed = millis() - _timePressed;
        }
        else _timeFlag = false;
        
        // Reads and stores the state of the switch.
        if (digitalRead(_pin) != _readingFlag && millis() - _elapsedTime > PRESET_DELAY)
        {
            _readingFlag = !_readingFlag;

            if (!digitalRead(_pin)) _switchPressed = true;
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
            this->getTimePressed() > MIN_SWITCH_TIME
            && 
            this->getTimePressed() < MAX_SWITCH_TIME
        );
    }

    bool switchLongPress(void) { return (this->getSwitchPressed() && this->getTimePressed() > MAX_SWITCH_TIME); }

    /* STATICS */
    static const uint16_t MAX_SWITCH_TIME = 500;
    static const uint8_t  MIN_SWITCH_TIME = 50;
    static const uint8_t  PRESET_DELAY    = 20;
};

#endif