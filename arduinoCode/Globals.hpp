#ifndef _GLOBALS__HPP_
#define _GLOBALS__HPP_

#include <Arduino.h>

#include <HID-Project.h>
#include <HID-Settings.h>

#define LEFT_LAYOUT
#define RIGHT_LAYOUT
#define NUMPAD_LAYOUT

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

struct KeyCodes
{
    static const uint KEY_RESERVED     = 0U;
    static const uint KEY_ESC          = 41U;
    static const uint KEY_F1           = 58U;
    static const uint KEY_F2           = 59U;
    static const uint KEY_F3           = 60U;
    static const uint KEY_F4           = 61U;
    static const uint KEY_F5           = 62U;
    static const uint KEY_F6           = 63U;
    static const uint KEY_F7           = 64U;
    static const uint KEY_F8           = 65U;
    static const uint KEY_F9           = 66U;
    static const uint KEY_F10          = 67U;
    static const uint KEY_F11          = 68U;
    static const uint KEY_F12          = 69U;
    static const uint KEY_PRINT        = 70U;
    static const uint KEY_DEL          = 76U;
    static const uint KEY_0            = 39U;
    static const uint KEY_1            = 30U;
    static const uint KEY_2            = 31U;
    static const uint KEY_3            = 32U;
    static const uint KEY_4            = 33U;
    static const uint KEY_5            = 34U;
    static const uint KEY_6            = 35U;
    static const uint KEY_7            = 36U;
    static const uint KEY_8            = 37U;
    static const uint KEY_9            = 38U;
    static const uint KEY_0            = 39U;
    static const uint KEY_MINUS        = 45U;
    static const uint KEY_EQUAL        = 46U;
    static const uint KEY_BACKSPACE    = 42U;
    static const uint KEY_TAB          = 43U;
    static const uint KEY_Q            = 20U;
    static const uint KEY_W            = 26U;
    static const uint KEY_E            = 8U;
    static const uint KEY_R            = 21U;
    static const uint KEY_T            = 23U;
    static const uint KEY_Y            = 28U;
    static const uint KEY_U            = 24U;
    static const uint KEY_I            = 12U;
    static const uint KEY_O            = 18U;
    static const uint KEY_P            = 19U;
    static const uint KEY_LEFT_BRACE   = 47U;
    static const uint KEY_RIGHT_BRACE  = 48U;
    static const uint KEY_BACKSLASH    = 49U;
    static const uint KEY_CAPS_LOCK    = 57U;
    static const uint KEY_A            = 4U;
    static const uint KEY_S            = 22U;
    static const uint KEY_D            = 7U;
    static const uint KEY_F            = 9U;
    static const uint KEY_G            = 10U;
    static const uint KEY_H            = 11U;
    static const uint KEY_J            = 13U;
    static const uint KEY_K            = 14U;
    static const uint KEY_L            = 15U;
    static const uint KEY_SEMICOLON    = 51U;
    static const uint KEY_TILDE        = 53U;
    static const uint KEY_QUOTE        = 52U;
    static const uint KEY_ENTER        = 40U;
    static const uint KEY_LEFT_SHIFT   = 225U;
    static const uint KEY_Z            = 29U;
    static const uint KEY_X            = 27U;
    static const uint KEY_C            = 6U;
    static const uint KEY_V            = 25U;
    static const uint KEY_B            = 5U;
    static const uint KEY_N            = 17U;
    static const uint KEY_M            = 16U;
    static const uint KEY_COMMA        = 54U;
    static const uint KEY_PERIOD       = 55U;
    static const uint KEY_SLASH        = 56U;
    static const uint KEY_RIGHT_SHIFT  = 229U;
    static const uint KEY_UP           = 82U;
    static const uint KEY_LEFT_CTRL    = 224U;
    static const uint KEY_OS           = 227U;
    static const uint KEY_LEFT_ALT     = 226U;
    static const uint KEY_LEFT_SPACE   = 44U;
    static const uint KEY_RIGHT_SPACE  = 44U;
    static const uint KEY_RIGHT_ALT    = 230U;
    static const uint KEY_RIGHT_CTRL   = 228U;
    static const uint KEY_LEFT         = 80U;
    static const uint KEY_DOWN         = 81U;
    static const uint KEY_RIGHT        = 79U;
    static const uint KEY_NUM_LOCK     = 83U;
    static const uint KEY_NUMPAD_1     = 0x59;
    static const uint KEY_NUMPAD_2     = 0x5A;
    static const uint KEY_NUMPAD_3     = 0x5B;
    static const uint KEY_NUMPAD_4     = 0x5C;
    static const uint KEY_NUMPAD_5     = 0x5D;
    static const uint KEY_NUMPAD_6     = 0x5E;
    static const uint KEY_NUMPAD_7     = 0x5F;
    static const uint KEY_NUMPAD_8     = 0x60;
    static const uint KEY_NUMPAD_9     = 0x61;
    static const uint KEY_NUMPAD_0     = 0x62;
    static const uint KEY_NUMPAD_DOT   = 99U;
    static const uint KEY_NUMPAD_DIV   = 0x54;
    static const uint KEY_NUMPAD_MULT  = 0x55;
    static const uint KEY_NUMPAD_SUBS  = 0x56;
    static const uint KEY_NUMPAD_ADD   = 0x57;
    static const uint KEY_NUMPAD_ENTER = 0x58;
    static const uint KEY_MODIFIER     = 900U;
};

#ifdef RIGHT_LAYOUT
uint KEYCODE_MATRIX[6][9] =
{
    { KeyCodes::KEY_F7, KeyCodes::KEY_F8,          KeyCodes::KEY_F9,        KeyCodes::KEY_F10,      KeyCodes::KEY_F11,        KeyCodes::KEY_F12,         KeyCodes::KEY_PRINT,       KeyCodes::KEY_DEL,       KeyCodes::KEY_RESERVED },
    { KeyCodes::KEY_7,  KeyCodes::KEY_8,           KeyCodes::KEY_9,         KeyCodes::KEY_0,        KeyCodes::KEY_MINUS,      KeyCodes::KEY_EQUAL,       KeyCodes::KEY_BACKSPACE,   NULL,                    KeyCodes::KEY_RESERVED },
    { KeyCodes::KEY_Y,  KeyCodes::KEY_U,           KeyCodes::KEY_I,         KeyCodes::KEY_O,        KeyCodes::KEY_P,          KeyCodes::KEY_LEFT_BRACE,  KeyCodes::KEY_RIGHT_BRACE, KeyCodes::KEY_BACKSLASH, KeyCodes::KEY_RESERVED },
    { KeyCodes::KEY_H,  KeyCodes::KEY_J,           KeyCodes::KEY_K,         KeyCodes::KEY_L,        KeyCodes::KEY_SEMICOLON,  KeyCodes::KEY_QUOTE,       KeyCodes::KEY_ENTER,       NULL,                    KeyCodes::KEY_RESERVED },
    { KeyCodes::KEY_N,  KeyCodes::KEY_M,           KeyCodes::KEY_COMMA,     KeyCodes::KEY_PERIOD,   KeyCodes::KEY_SLASH,      KeyCodes::KEY_RIGHT_SHIFT, KeyCodes::KEY_UP,          NULL,                    KeyCodes::KEY_RESERVED },
    { NULL,             KeyCodes::KEY_RIGHT_SPACE, KeyCodes::KEY_RIGHT_ALT, KeyCodes::KEY_MODIFIER, KeyCodes::KEY_RIGHT_CTRL, KeyCodes::KEY_LEFT,        KeyCodes::KEY_DOWN,        KeyCodes::KEY_RIGHT,     NULL }
};
#endif
#ifdef LEFT_LAYOUT
uint KEYCODE_MATRIX[6][9] =
{
    { KeyCodes::KEY_ESC,        KeyCodes::KEY_F1, KeyCodes::KEY_F2,       KeyCodes::KEY_F3,         KeyCodes::KEY_F4, KeyCodes::KEY_F5, KeyCodes::KEY_F6, NULL, NULL },
    { KeyCodes::KEY_TILDE,      KeyCodes::KEY_1,  KeyCodes::KEY_2,        KeyCodes::KEY_3,          KeyCodes::KEY_4,  KeyCodes::KEY_5,  KeyCodes::KEY_6,  NULL, NULL },
    { KeyCodes::KEY_TAB,        KeyCodes::KEY_Q,  KeyCodes::KEY_W,        KeyCodes::KEY_E,          KeyCodes::KEY_R,  KeyCodes::KEY_T,  NULL,             NULL, NULL },
    { KeyCodes::KEY_CAPS_LOCK,  KeyCodes::KEY_A,  KeyCodes::KEY_S,        KeyCodes::KEY_D,          KeyCodes::KEY_F,  KeyCodes::KEY_G,  NULL,             NULL, NULL },
    { KeyCodes::KEY_LEFT_SHIFT, KeyCodes::KEY_Z,  KeyCodes::KEY_X,        KeyCodes::KEY_C,          KeyCodes::KEY_V,  KeyCodes::KEY_B,  NULL,             NULL, NULL },
    { KeyCodes::KEY_LEFT_CTRL,  KeyCodes::KEY_OS, KeyCodes::KEY_LEFT_ALT, KeyCodes::KEY_LEFT_SPACE, NULL,             NULL,             NULL,             NULL, NULL }
};
#endif
#ifdef NUMPAD_LAYOUT
uint KEYCODE_MATRIX[6][9] =
{
    { KeyCodes::KEY_RESERVED, KeyCodes::KEY_RESERVED,   KeyCodes::KEY_RESERVED,    KeyCodes::KEY_RESERVED,     NULL, NULL, NULL, NULL, NULL },
    { KeyCodes::KEY_NUM_LOCK, KeyCodes::KEY_NUMPAD_DIV, KeyCodes::KEY_NUMPAD_MULT, KeyCodes::KEY_NUMPAD_SUBS,  NULL, NULL, NULL, NULL, NULL },
    { KeyCodes::KEY_NUMPAD_7, KeyCodes::KEY_NUMPAD_8,   KeyCodes::KEY_NUMPAD_9,    KeyCodes::KEY_NUMPAD_ADD,   NULL, NULL, NULL, NULL, NULL },
    { KeyCodes::KEY_NUMPAD_4, KeyCodes::KEY_NUMPAD_5,   KeyCodes::KEY_NUMPAD_6,    KeyCodes::KEY_NUMPAD_ADD,   NULL, NULL, NULL, NULL, NULL },
    { KeyCodes::KEY_NUMPAD_1, KeyCodes::KEY_NUMPAD_2,   KeyCodes::KEY_NUMPAD_3,    KeyCodes::KEY_NUMPAD_ENTER, NULL, NULL, NULL, NULL, NULL },
    { KeyCodes::KEY_NUMPAD_0, KeyCodes::KEY_NUMPAD_0,   KeyCodes::KEY_NUMPAD_DOT,  KeyCodes::KEY_NUMPAD_ENTER, NULL, NULL, NULL, NULL, NULL }
};
#endif


bool* charToBoolArray(const byte incomingByte)
{
    bool result[8] = { 0 };
    for (int i = 0; i < 8; i++)
        result[i] = (incomingByte & (1 << i)) != 0;

    return result;
}

int indicesToKeystroke(int i, int j)
{

}

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