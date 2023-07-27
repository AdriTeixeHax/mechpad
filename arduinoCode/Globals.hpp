#ifndef _GLOBALS__HPP_
#define _GLOBALS__HPP_

#include <Arduino.h>

using uint = unsigned int;
using string = const char*;

enum class MachineState { startup, running, stripConfig, encoderConfig, error };
enum class StripConfigState { none, speed, length, brightness };

constexpr byte PWM_PINS[7] = { 3, 5, 6, 9, 10, 11, 13 };
constexpr byte ENCODER_PIN_A  = 3;
constexpr byte ENCODER_PIN_B  = 4;
constexpr byte ENCODER_PIN_SW = 5;
constexpr byte STRIP_PIN = 6;
constexpr byte SR_PIN_LOAD = 8;
constexpr byte SR_PIN_EN   = 9;
constexpr byte SR_PIN_DATA = 10;
constexpr byte SR_PIN_CLK  = 11;

// template<typename Type>
// struct ParamData
// {
//     String _name;
//     Type   _value;
//     Type   _maxValue;
//     Type   _minValue;

//     explicit ParamData(const String& name, const Type initialValue, const Type maxValue, const Type minValue) :
//         _name(name), _value(initialValue), _maxValue(maxValue), _minValue(minValue)
//     {
//         if (initialValue < minValue) _value = minValue;
//         if (initialValue > maxValue) _value = maxValue;
//     }

//     void increaseValue(const Type increment)
//     {
//         if (_value + increment <= _maxValue && _value + increment >= _minValue)
//             _value += increment;
//     }

//     void resetValue(void) { _value = 0; }
//     void resetAll  (void) { _value = 0; _maxValue = 0; _minValue = 0; }

//     bool isMax(void) { return (_value == _maxValue); }
//     bool isMin(void) { return (_value == _minValue); }
// };

#endif