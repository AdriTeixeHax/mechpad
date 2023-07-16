#include "Coordinator.hpp"

#include <HID-Project.h>
#include <HID-Settings.h>

#define DEBUG

Coordinator::Coordinator(void) :
    _machineState(MachineState::startup),
    _stateFlags(),
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
            _machineState = MachineState::running;
        break;

    default:
        break;
    }

/* ACTIONS ACCORDING TO STATE */
    switch (_machineState)
    {
    case MachineState::startup:
        // LCD Update //
        if (!_stateFlags._startup)
        {
            _LCDScreen.print("MechPad Project", "State: startup");
        }

        break;

    case MachineState::running:
        // LCD Update //
        if (!_stateFlags._running)
        {
            _LCDScreen.print("MechPad Project", "State: running");
        } 
        
        // Encoder rotation reading //
        _rotaryEncoder.reading();
        if (_rotaryEncoder.getLastData().hasBeenRotated)
        {
            if (!_rotaryEncoder.getLastData().direction)
                Consumer.write(MEDIA_VOL_UP);
            else
                Consumer.write(MEDIA_VOL_DOWN);
        }

        // Encoder switch reading //
        if (_rotaryEncoder.switchUpdate())
        {
            if (_rotaryEncoder.getSwitchPressed())
                Consumer.write(MEDIA_PLAY_PAUSE);
        }

        break;

    case MachineState::stripConfig:
        // LCD Update //
        if (!_stateFlags._stripConfig)
        {
            _LCDScreen.print("MechPad Project", "State: LED Conf.");
        } 
        
        // Encoder rotation reading //
        _rotaryEncoder.reading();
        if (_rotaryEncoder.getLastData().hasBeenRotated)
        {
            if (!_rotaryEncoder.getLastData().direction)
            {
                // switch (_stripConfigState)
                // {
                // case StripConfigState::speed:
                //     _RGBStrip.increaseEffectSpeed(_rotaryEncoder.getResolution());
                //     break;

                // case StripConfigState::length:
                //     _RGBStrip.increaseEffectSpeed
                // }
            }
            else
                Consumer.write(MEDIA_VOL_DOWN);
        }

        // Encoder switch reading //
        if (_rotaryEncoder.switchUpdate())
        {
            if (_rotaryEncoder.getSwitchPressed())
                Consumer.write(MEDIA_PLAY_PAUSE);
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