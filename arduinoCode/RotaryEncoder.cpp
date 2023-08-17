#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t pinA, uint8_t pinB) :
    _pinA(pinA),
    _pinB(pinB),
    _currentState(false),
    _lastState(false),
    _resolution(1),
    _maxResolution(10),
    _lastReadData()
{
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT); 

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