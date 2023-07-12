#ifndef _GLOBALS__HPP_
#define _GLOBALS__HPP_

#include <Arduino.h>

using uint = unsigned int;

constexpr byte PWM_PINS[7] = { 3, 5, 6, 9, 10, 11, 13 };
constexpr byte ENCODER_PIN_A  = 3;
constexpr byte ENCODER_PIN_B  = 4;
constexpr byte ENCODER_PIN_SW = 5;
constexpr byte STRIP_PIN = 6;

#endif