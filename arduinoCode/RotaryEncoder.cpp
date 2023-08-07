#include "RotaryEncoder.h"

constexpr uint8_t PRESET_DELAY = 20;

RotaryEncoder::RotaryEncoder(uint8_t pinA, uint8_t pinB, uint8_t pinSwitch) :
    _pinA(pinA),
    _pinB(pinB),
    _pinSwitch(pinSwitch),
    _currentState(false),
    _lastState(false),
    _switchPressed(false),
    _resolution(1),
    _maxResolution(10),
    _lastReadData()
{
    pinMode(_pinA,      INPUT);
    pinMode(_pinB,      INPUT); 
    pinMode(_pinSwitch, INPUT);

    _lastState = digitalRead(_pinA);
} 

bool RotaryEncoder::incrCounter(int incr)
{
    if (_resolution + incr <= _maxResolution && _resolution + incr >= 0)
    {
        _resolution += incr;
        return true;
    }
    else return false;
}

void RotaryEncoder::reading(void)
{
    _lastReadData.reset();
    // Reads the pin A and assigns a corresponding value to the _currentState variable.
    _currentState = digitalRead(_pinA);

    // If the last and current state of the rotary encoder's pin A are different, then a pulse occurred.
    if (_currentState != _lastState && _currentState == 1)
    {
        _lastReadData.hasBeenRotated = true;

        if (digitalRead(_pinB) != _currentState)
        {
            _lastReadData.direction = true;
            _lastReadData.counter--;
        }
        else
        {
            _lastReadData.direction = false;
            _lastReadData.counter++;
        }
    }
    // Save the state of the current operation to compare it to the next one.
    _lastState = _currentState;
}

bool RotaryEncoder::switchUpdate(void)
{
    // Flags to prevent double counting.
    static bool flag = false;
    static bool timeFlag = false;
    // Time variables for debouncing and counting how much time since the switch was pressed.
    static unsigned long elapsedTime = 0;
    static unsigned long timePressed = 0;

    // Stores the time the switch has been pressed.
    if (!digitalRead(_pinSwitch))
    {
        if (!timeFlag)
        {
            timePressed = millis();
            timeFlag = !timeFlag;
        }
        _timePressed = millis() - timePressed;
    }
    else timeFlag = false;
    
    // Reads and stores the state of the switch.
    if (digitalRead(_pinSwitch) != flag && millis() - elapsedTime > PRESET_DELAY)
    {
        flag = !flag;

        if (!digitalRead(_pinSwitch)) _switchPressed = true;
        else _switchPressed = false;

        elapsedTime = millis();

        return true;
    }
    else return false;
}