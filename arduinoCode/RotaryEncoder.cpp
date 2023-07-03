#include "RotaryEncoder.hpp"

RotaryEncoder::RotaryEncoder(uint pinA, uint pinB, uint pinSwitch) :
    _pinA(pinA),
    _pinB(pinB),
    _pinSwitch(pinSwitch),
    _currentState(false),
    _lastState(false),
    _switchPressed(false),
    _counter(0),
    _resolution(1),
    _maxResolution(10),
    _delayTime(250)
{
    pinMode(this->_pinA,      INPUT);
    pinMode(this->_pinB,      INPUT);
    pinMode(this->_pinSwitch, INPUT_PULLUP);

    this->_lastState = digitalRead(_pinA);
}

bool RotaryEncoder::incrCounter(int incr)
{
    if (this->_resolution + incr <= this->_maxResolution && this->_resolution + incr >= 0)
    {
        this->_resolution += incr;
        return true;
    }
    else return false;
}

ReadingData RotaryEncoder::reading(void)
{
    // Variable for returning value.
    static ReadingData result = ReadingData(false, false);
    result.reset();

    // Reads the pin A and assigns a corresponding value to the _currentState variable.
    this->_currentState = digitalRead(this->_pinA);

    // If the last and current state of the rotary encoder's pin A are different, then a pulse occurred
    if (this->_currentState != this->_lastState)
    {
        result._hasBeenRotated = true;

        if (digitalRead(_pinB) != this->_currentState)
            result._direction = true;
        else
            result._direction = false;
    }
    // Save the state of the current operation to compare it to the next one.
    this->_lastState = this->_currentState;

    return result;
}

bool RotaryEncoder::switchUpdate(void)
{
    if (errorChecking()) return false;

    static bool temp = digitalRead(_pinSwitch);

    if (digitalRead(_pinSwitch))
        this->_switchPressed = true;
    else
        this->_switchPressed = false;

    if (digitalRead(_pinSwitch) == temp)
    {
        temp = digitalRead(_pinSwitch);
        return false;
    }
    else
    {
        temp = digitalRead(_pinSwitch);
        return true;
    }
}