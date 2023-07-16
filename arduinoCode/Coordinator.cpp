#include "Coordinator.hpp"

#include <HID-Project.h>
#include <HID-Settings.h>

#define DEBUG

Coordinator::Coordinator(void) :
    _machineState(MachineState::startup),
    _stateFlags(),
    _stripConfigState(StripConfigState::brightness),
    _LCDScreen(0x27, 16, 2),
    _rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_SW),
    _RGBStrip(STRIP_PIN, 6, 4)
{
    Consumer.begin();
}

void Coordinator::loop(void)
{
/* STATE TRANSITIONS */

    switch (_machineState)
    {
    case MachineState::startup:
        static unsigned long elapsedTime = millis();
        if (millis() - elapsedTime > 1000)
        {
            _machineState = MachineState::running;
            elapsedTime = millis();
        }
        break;

    case MachineState::running:
        if (_rotaryEncoder.getSwitchPressed() && _rotaryEncoder.getTimePressed() > 500)
        {
            _rotaryEncoder.resetTimePressed();
            _machineState = MachineState::stripConfig;
        }
        break;

    case MachineState::stripConfig:
        if (_rotaryEncoder.getSwitchPressed() && _rotaryEncoder.getTimePressed() > 500)
        {
            _rotaryEncoder.resetTimePressed();
            _machineState = MachineState::running;
        }

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
        if (_rotaryEncoder.switchUpdate() && _rotaryEncoder.getSwitchPressed())
            Consumer.write(MEDIA_PLAY_PAUSE);

        break;

    case MachineState::stripConfig:      

        static string bottomLine = "";

        // Encoder rotation reading //
        _rotaryEncoder.reading();
        if (_rotaryEncoder.getLastData().hasBeenRotated)
        {
            static short int sign = 0;
            if (_rotaryEncoder.getLastData().direction) sign = -1;
            else sign = 0;

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
        if (_rotaryEncoder.switchUpdate() && _rotaryEncoder.getSwitchPressed())
        {
            switch (_stripConfigState)
            {
            case StripConfigState::brightness:
                bottomLine = "Brightness";
                _stripConfigState = StripConfigState::length;
                break;

            case StripConfigState::length:
                bottomLine = "Length";
                _stripConfigState = StripConfigState::speed;
                break;
            
            case StripConfigState::speed:
                bottomLine = "Speed";
                _stripConfigState = StripConfigState::brightness;
                _machineState = MachineState::running;
                break;

            default:
                break;
            }
        }

        // LCD Update //
        _LCDScreen.printOnce("LED Config.", bottomLine);

        break;

    default:
        break;
    }

/* RGB CONTROL */
    _RGBStrip.effectState(_machineState);

/* FLAG RESETTING */
    _stateFlags.resetExcept(_machineState);
}