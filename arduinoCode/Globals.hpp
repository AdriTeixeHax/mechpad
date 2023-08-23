#ifndef _GLOBALS__HPP_
#define _GLOBALS__HPP_

#include <Arduino.h>

#include <HID-Project.h>
#include <HID-Settings.h>

//#define LEFT_LAYOUT
//#define RIGHT_LAYOUT
//#define NUMPAD_LAYOUT
#define TESTING_LAYOUT

using string = const char*;

enum class MachineState { startup, running, stripConfig, encoderConfig, error };
enum class StripConfigState { none, speed, length, brightness };

constexpr uint8_t PWM_PINS[7] = { 3, 5, 6, 9, 10, 11, 13 };

constexpr uint8_t ENCODER_PIN_A = 6;
constexpr uint8_t ENCODER_PIN_B = 7;

constexpr uint8_t STRIP_PIN     = 5;

constexpr uint8_t SR_PIN_LOAD   = 8;
constexpr uint8_t SR_PIN_EN     = 9;
constexpr uint8_t SR_PIN_DATA   = 10;
constexpr uint8_t SR_PIN_CLK    = 11;

constexpr uint8_t BASE_COL_PIN  = 8;
constexpr uint8_t BASE_ROW_PIN  = A0;

struct KeyCodes
{
    static const uint16_t KEY_RESERVED     = 0U;
    static const uint16_t KEY_ESC          = 41U;
    static const uint16_t KEY_F1           = 58U;
    static const uint16_t KEY_F2           = 59U;
    static const uint16_t KEY_F3           = 60U;
    static const uint16_t KEY_F4           = 61U;
    static const uint16_t KEY_F5           = 62U;
    static const uint16_t KEY_F6           = 63U;
    static const uint16_t KEY_F7           = 64U;
    static const uint16_t KEY_F8           = 65U;
    static const uint16_t KEY_F9           = 66U;
    static const uint16_t KEY_F10          = 67U;
    static const uint16_t KEY_F11          = 68U;
    static const uint16_t KEY_F12          = 69U;
    static const uint16_t KEY_PRINT        = 70U;
    static const uint16_t KEY_DEL          = 76U;
    static const uint16_t KEY_0            = 39U;
    static const uint16_t KEY_1            = 30U;
    static const uint16_t KEY_2            = 31U;
    static const uint16_t KEY_3            = 32U;
    static const uint16_t KEY_4            = 33U;
    static const uint16_t KEY_5            = 34U;
    static const uint16_t KEY_6            = 35U;
    static const uint16_t KEY_7            = 36U;
    static const uint16_t KEY_8            = 37U;
    static const uint16_t KEY_9            = 38U;
    static const uint16_t KEY_MINUS        = 45U;
    static const uint16_t KEY_EQUAL        = 46U;
    static const uint16_t KEY_BACKSPACE    = 42U;
    static const uint16_t KEY_TAB          = 43U;
    static const uint16_t KEY_Q            = 20U;
    static const uint16_t KEY_W            = 26U;
    static const uint16_t KEY_E            = 8U;
    static const uint16_t KEY_R            = 21U;
    static const uint16_t KEY_T            = 23U;
    static const uint16_t KEY_Y            = 28U;
    static const uint16_t KEY_U            = 24U;
    static const uint16_t KEY_I            = 12U;
    static const uint16_t KEY_O            = 18U;
    static const uint16_t KEY_P            = 19U;
    static const uint16_t KEY_LEFT_BRACE   = 47U;
    static const uint16_t KEY_RIGHT_BRACE  = 48U;
    static const uint16_t KEY_BACKSLASH    = 49U;
    static const uint16_t KEY_CAPS_LOCK    = 57U;
    static const uint16_t KEY_A            = 4U;
    static const uint16_t KEY_S            = 22U;
    static const uint16_t KEY_D            = 7U;
    static const uint16_t KEY_F            = 9U;
    static const uint16_t KEY_G            = 10U;
    static const uint16_t KEY_H            = 11U;
    static const uint16_t KEY_J            = 13U;
    static const uint16_t KEY_K            = 14U;
    static const uint16_t KEY_L            = 15U;
    static const uint16_t KEY_SEMICOLON    = 51U;
    static const uint16_t KEY_TILDE        = 53U;
    static const uint16_t KEY_QUOTE        = 52U;
    static const uint16_t KEY_ENTER        = 40U;
    static const uint16_t KEY_LEFT_SHIFT   = 225U;
    static const uint16_t KEY_Z            = 29U;
    static const uint16_t KEY_X            = 27U;
    static const uint16_t KEY_C            = 6U;
    static const uint16_t KEY_V            = 25U;
    static const uint16_t KEY_B            = 5U;
    static const uint16_t KEY_N            = 17U;
    static const uint16_t KEY_M            = 16U;
    static const uint16_t KEY_COMMA        = 54U;
    static const uint16_t KEY_PERIOD       = 55U;
    static const uint16_t KEY_SLASH        = 56U;
    static const uint16_t KEY_RIGHT_SHIFT  = 229U;
    static const uint16_t KEY_UP           = 82U;
    static const uint16_t KEY_LEFT_CTRL    = 224U;
    static const uint16_t KEY_OS           = 227U;
    static const uint16_t KEY_LEFT_ALT     = 226U;
    static const uint16_t KEY_LEFT_SPACE   = 44U;
    static const uint16_t KEY_RIGHT_SPACE  = 44U;
    static const uint16_t KEY_RIGHT_ALT    = 230U;
    static const uint16_t KEY_RIGHT_CTRL   = 228U;
    static const uint16_t KEY_LEFT         = 80U;
    static const uint16_t KEY_DOWN         = 81U;
    static const uint16_t KEY_RIGHT        = 79U;
    static const uint16_t KEY_NUM_LOCK     = 83U;
    static const uint16_t KEY_NUMPAD_1     = 0x59;
    static const uint16_t KEY_NUMPAD_2     = 0x5A;
    static const uint16_t KEY_NUMPAD_3     = 0x5B;
    static const uint16_t KEY_NUMPAD_4     = 0x5C;
    static const uint16_t KEY_NUMPAD_5     = 0x5D;
    static const uint16_t KEY_NUMPAD_6     = 0x5E;
    static const uint16_t KEY_NUMPAD_7     = 0x5F;
    static const uint16_t KEY_NUMPAD_8     = 0x60;
    static const uint16_t KEY_NUMPAD_9     = 0x61;
    static const uint16_t KEY_NUMPAD_0     = 0x62;
    static const uint16_t KEY_NUMPAD_DOT   = 99U;
    static const uint16_t KEY_NUMPAD_DIV   = 0x54;
    static const uint16_t KEY_NUMPAD_MULT  = 0x55;
    static const uint16_t KEY_NUMPAD_SUBS  = 0x56;
    static const uint16_t KEY_NUMPAD_ADD   = 0x57;
    static const uint16_t KEY_NUMPAD_ENTER = 0x58;

    static const uint16_t THRESHOLD        = 500U;
    static const uint16_t KEY_ENCODER_0    = 800U;
    static const uint16_t KEY_ENCODER_1    = 801U;
    static const uint16_t KEY_ENCODER_2    = 802U;
    static const uint16_t KEY_ENCODER_3    = 803U;
    static const uint16_t KEY_ENCODER_4    = 804U;
    static const uint16_t KEY_MODIFIER     = 900U;
};

#ifdef RIGHT_LAYOUT
constexpr uint8_t ROW_COUNT = 6;
constexpr uint8_t COL_COUNT = 9;

static uint8_t ROW_PINS[ROW_COUNT] = { A0, A1, A2, A3, A4, A5 };

static uint16_t KEYCODE_MATRIX[ROW_COUNT][COL_COUNT] =
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
constexpr uint8_t ROW_COUNT = 6;
constexpr uint8_t COL_COUNT = 7;

static uint8_t ROW_PINS[ROW_COUNT] = { A0, A1, A2, A3, A4, A5 };

static uint16_t KEYCODE_MATRIX[ROW_COUNT][COL_COUNT] =
{
    { KeyCodes::KEY_ESC,        KeyCodes::KEY_F1, KeyCodes::KEY_F2,       KeyCodes::KEY_F3,         KeyCodes::KEY_F4, KeyCodes::KEY_F5, KeyCodes::KEY_F6},
    { KeyCodes::KEY_TILDE,      KeyCodes::KEY_1,  KeyCodes::KEY_2,        KeyCodes::KEY_3,          KeyCodes::KEY_4,  KeyCodes::KEY_5,  KeyCodes::KEY_6},
    { KeyCodes::KEY_TAB,        KeyCodes::KEY_Q,  KeyCodes::KEY_W,        KeyCodes::KEY_E,          KeyCodes::KEY_R,  KeyCodes::KEY_T,  NULL           },
    { KeyCodes::KEY_CAPS_LOCK,  KeyCodes::KEY_A,  KeyCodes::KEY_S,        KeyCodes::KEY_D,          KeyCodes::KEY_F,  KeyCodes::KEY_G,  NULL           },
    { KeyCodes::KEY_LEFT_SHIFT, KeyCodes::KEY_Z,  KeyCodes::KEY_X,        KeyCodes::KEY_C,          KeyCodes::KEY_V,  KeyCodes::KEY_B,  NULL           },
    { KeyCodes::KEY_LEFT_CTRL,  KeyCodes::KEY_OS, KeyCodes::KEY_LEFT_ALT, KeyCodes::KEY_LEFT_SPACE, NULL,             NULL,             NULL           }
};
#endif

#ifdef NUMPAD_LAYOUT
constexpr uint8_t ROW_COUNT = 6;
constexpr uint8_t COL_COUNT = 4;

static uint8_t ROW_PINS[ROW_COUNT] = { A0, A1, A2, A3, A4, A5 };

static uint16_t KEYCODE_MATRIX[ROW_COUNT][COL_COUNT] =
{
    { KeyCodes::KEY_RESERVED, KeyCodes::KEY_RESERVED,   KeyCodes::KEY_RESERVED,    KeyCodes::KEY_RESERVED    },
    { KeyCodes::KEY_NUM_LOCK, KeyCodes::KEY_NUMPAD_DIV, KeyCodes::KEY_NUMPAD_MULT, KeyCodes::KEY_NUMPAD_SUBS },
    { KeyCodes::KEY_NUMPAD_7, KeyCodes::KEY_NUMPAD_8,   KeyCodes::KEY_NUMPAD_9,    KeyCodes::KEY_NUMPAD_ADD  },
    { KeyCodes::KEY_NUMPAD_4, KeyCodes::KEY_NUMPAD_5,   KeyCodes::KEY_NUMPAD_6,    KeyCodes::KEY_NUMPAD_ADD  },
    { KeyCodes::KEY_NUMPAD_1, KeyCodes::KEY_NUMPAD_2,   KeyCodes::KEY_NUMPAD_3,    KeyCodes::KEY_NUMPAD_ENTER},
    { KeyCodes::KEY_NUMPAD_0, KeyCodes::KEY_NUMPAD_0,   KeyCodes::KEY_NUMPAD_DOT,  KeyCodes::KEY_NUMPAD_ENTER}
};
#endif

#ifdef TESTING_LAYOUT
constexpr uint8_t ROW_COUNT = 3;
constexpr uint8_t COL_COUNT = 4;

static uint8_t ROW_PINS[ROW_COUNT] = { A0, A1, A2 };

static uint16_t KEYCODE_MATRIX[ROW_COUNT][COL_COUNT] =
{
    { KeyCodes::KEY_A, KeyCodes::KEY_B, KeyCodes::KEY_C, KeyCodes::KEY_ENCODER_0 },
    { KeyCodes::KEY_E, KeyCodes::KEY_F, KeyCodes::KEY_G, KeyCodes::KEY_H },
    { KeyCodes::KEY_I, KeyCodes::KEY_J, KeyCodes::KEY_K, KeyCodes::KEY_L }
};
#endif

inline bool* charToBoolArray(const uint8_t incomingByte)
{
    bool result[8] = { 0 };
    for (int i = 0; i < 8; i++)
        result[i] = (incomingByte & (1 << i)) != 0;

    return result;
}

#endif