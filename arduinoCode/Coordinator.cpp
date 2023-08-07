#include "Coordinator.hpp"

#include <HID-Project.h>
#include <HID-Settings.h>

Coordinator::Coordinator(void) :
    _machineState(MachineState::startup),
    _stateFlags(),
    _stripConfigState(StripConfigState::brightness),
    _LCDScreen(0x27, 16, 2),
    _rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_SW),
    _RGBStrip(STRIP_PIN, 6, 4)
    //_keyboardMatrix(NUM_COLS, PINS_COLS, SR_PIN_LOAD, SR_PIN_EN, SR_PIN_DATA, SR_PIN_CLK)
{
    Consumer.begin();
    Serial.begin(9600);
}

void Coordinator::loop(void)
{ 
/* STATE TRANSITIONS */
    switch (_machineState)
    {
    case MachineState::startup:
        static unsigned long elapsedTime = millis();
        if (millis() - elapsedTime > STARTUP_TIMEOUT)
        {
            _rotaryEncoder.resetTimePressed();
            _machineState = MachineState::running;
            elapsedTime = millis();
        }
        break;

    case MachineState::running:
        if (_rotaryEncoder.switchLongPress())
        {
            _rotaryEncoder.resetTimePressed();
            _machineState = MachineState::stripConfig;
        }
        break;

    case MachineState::stripConfig:
        if (_rotaryEncoder.switchLongPress())
        {
            _rotaryEncoder.resetTimePressed();
            _machineState = MachineState::running;
            _stripConfigState = StripConfigState::brightness;
        }
        break;

    default:
        break;
    }

/* ACTIONS ACCORDING TO STATE */
    switch (_machineState)
    {
    case MachineState::running:
        // LCD Update //
        _LCDScreen.printOnce("MechPad Project", "Running");
        
        // Encoder rotation reading //
        _rotaryEncoder.reading();
        if (_rotaryEncoder.getLastData().hasBeenRotated)
        {
            if (!_rotaryEncoder.getLastData().direction) // Clockwise
                Consumer.write(MEDIA_VOL_UP);
            else
                Consumer.write(MEDIA_VOL_DOWN);
        }

        // Encoder switch reading //
        if (_rotaryEncoder.switchPress())
            Consumer.write(MEDIA_PLAY_PAUSE);

        // Keyboard matrix reading //
        // KeyboardData* keyboardData = _keyboardMatrix.keypress();
        // for (byte i = 0; i < keyboardData->getNumElem(); i++)
        // {
        //     Consumer.write(static_cast<ConsumerKeycode>((*keyboardData)[i]));
        // }

        break;

    case MachineState::stripConfig:
        // LCD Update //
        static string bottomLine = "";
        switch (_stripConfigState)
        {
        case StripConfigState::brightness:
            bottomLine = "Brightness";
            break;

        case StripConfigState::length:
            bottomLine = "Length";
            break;
        
        case StripConfigState::speed:
            bottomLine = "Speed";
            break;

        default:
            break;
        }
        _LCDScreen.printOnce("LED Config.", bottomLine);

        // Encoder rotation reading //
        _rotaryEncoder.reading();
        if (_rotaryEncoder.getLastData().hasBeenRotated)
        {
            static short int sign = 1;
            if (_rotaryEncoder.getLastData().direction) sign = -1;
            else sign = 1;

            switch (_stripConfigState)
            {
            case StripConfigState::speed:
                _RGBStrip.getRainbowEffect()->incrementSpeed(sign * _rotaryEncoder.getResolution());
                break;

            case StripConfigState::length:
                _RGBStrip.getRainbowEffect()->incrementLength(sign * _rotaryEncoder.getResolution());
                break;

            case StripConfigState::brightness:
                _RGBStrip.getRainbowEffect()->incrementBrightness(sign * _rotaryEncoder.getResolution());
                break;

            default:
                break;
            }
        }

        // Encoder switch reading //
        if (_rotaryEncoder.switchPress())
        {
            switch (_stripConfigState)
            {
            case StripConfigState::brightness:
                _stripConfigState = StripConfigState::length;
                break;

            case StripConfigState::length:
                _stripConfigState = StripConfigState::speed;
                break;
            
            case StripConfigState::speed:
                _stripConfigState = StripConfigState::brightness;
                _machineState = MachineState::running;
                break;

            default:
                break;
            }
        }

        break;

    default:
        break;
    }

/* RGB CONTROL */
    _RGBStrip.effectState(_machineState);

/* FLAG RESETTING */
    _stateFlags.resetExcept(_machineState);
}