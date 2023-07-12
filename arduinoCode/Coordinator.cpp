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
    if (_machineState == MachineState::startup)
    {
        static unsigned long elapsedTime = millis();
        if (millis() - elapsedTime > 1000)
            _machineState = MachineState::running;
    }

/* ACTIONS ACCORDING TO STATE */
    // Startup //
    if (_machineState == MachineState::startup)
    {
        // LCD Update //
        if (!_stateFlags._startup)
        {
            _LCDScreen.print("MechPad Project", "State: startup");
        }
        // RGB Control //
        _RGBStrip.effectStartup();
    }

    // Running //
    if (_machineState == MachineState::running)
    {
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

        // RGB Control //
        _RGBStrip.effectRainbow();
    }

    // Strip Configuration //
    if (_machineState == MachineState::stripConfig)
    {
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
                switch (stripConfigState)
                {
                case StripConfigState::speed:
                    _RGBStrip.increaseEffectSpeed(_rotaryEncoder.getResolution());
                    break;
                }
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

        // RGB Control //
        _RGBStrip.effectRainbow();
    }

/* FLAG RESETTING */
    _stateFlags.resetExcept(_machineState);
}