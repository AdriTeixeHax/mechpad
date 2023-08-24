#include "Coordinator.h"

#include <HID-Project.h>
#include <HID-Settings.h>

Coordinator::Coordinator(void) :
    _machineState(MachineState::startup),
    _stripConfigState(StripConfigState::brightness),
    _LCDScreen(0x27, 16, 2),
    _rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B),
    _RGBStrip(STRIP_PIN, 6, 4),
    _keyboardMatrix(true, SR_PIN_LOAD, SR_PIN_EN, SR_PIN_DATA, SR_PIN_CLK),
    _virtualSwitchList(30),
    _modeSwitch(&_virtualSwitchList)
{
    Consumer.begin();
    Keyboard.begin();
    _RGBStrip.reset();
}

void Coordinator::loop(void)
{
    // State transitions //
    stateTransitions();

    // Actions according to state //
    switch (_machineState)
    {
    case MachineState::running:
        running();
        break;

    case MachineState::stripConfig:
        stripConfig();
        break;

    default:
        break;
    }

    // RGB Control //
    _RGBStrip.effectState(_machineState);
}

void Coordinator::stateTransitions(void)
{
    switch (_machineState)
    {
    case MachineState::startup:
        static unsigned long elapsedTime = millis();
        if (millis() - elapsedTime > STARTUP_TIMEOUT)
        {
            _LCDScreen.clear();
            _modeSwitch.resetTimePressed();
            _machineState = MachineState::running;
            elapsedTime = millis();
        }
        break;

    case MachineState::running:
        if (_modeSwitch.switchLongPress())
        {
            _LCDScreen.clear();
            _modeSwitch.resetTimePressed();
            _machineState = MachineState::stripConfig;
        }
        break;

    case MachineState::stripConfig:
        if (_modeSwitch.switchLongPress())
        {
            _LCDScreen.clear();
            _modeSwitch.resetTimePressed();
            _machineState = MachineState::running;
            _stripConfigState = StripConfigState::brightness;
        }
        break;

    default:
        break;
    }
}

void Coordinator::running(void)
{
    // LCD Update //
    _LCDScreen.printOnce("MechPad Project", "by AdriTeixeHax");
    
    // Encoder rotation reading //
    _rotaryEncoder.reading();
    if (_rotaryEncoder.getLastData().hasBeenRotated)
    {
        if (!_rotaryEncoder.getLastData().direction) // Clockwise
            Consumer.write(MEDIA_VOL_UP);
        else
            Consumer.write(MEDIA_VOL_DOWN);
    }

    // Virtual switch reading //
    if (_modeSwitch.switchPress())
        Consumer.write(MEDIA_PLAY_PAUSE);

    // Keyboard matrix reading //
    _keyboardMatrix.keypress();
    static uint16_t buffer = 0;
    if (_keyboardMatrix.getLastData().size() != 0)
    {
        for (uint8_t i = 0; i < _keyboardMatrix.getLastData().size(); i++)
        {
            buffer = _keyboardMatrix.getLastData()[i];

            if (buffer < KeyCodes::THRESHOLD)
                Keyboard.press(static_cast<KeyboardKeycode>(buffer));
            else
                activateFromKeycode(buffer);
        }
    }
    else
    {
        Keyboard.releaseAll();
        deactivateAll();
    }
       
}

void Coordinator::stripConfig(void)
{
    // LCD Update //
    static string topLine = "";
    static uint8_t bottomLine = 0;
    switch (_stripConfigState)
    {
    case StripConfigState::brightness:
        topLine = "Brightness";
        bottomLine = _RGBStrip.getRainbowEffect()->getBrightness();
        break;

    case StripConfigState::length:
        topLine = "Length";
        bottomLine = _RGBStrip.getRainbowEffect()->getLength();
        break;
    
    case StripConfigState::speed:
        topLine = "Speed";
        bottomLine = _RGBStrip.getRainbowEffect()->getSpeed();
        break;

    default:
        break;
    }
    _LCDScreen.printOnce(topLine, bottomLine);

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

    // Keyboard matrix reading //
    _keyboardMatrix.keypress();
    if (_keyboardMatrix.getLastData().size() != 0)
    {
        for (uint8_t i = 0; i < _keyboardMatrix.getLastData().size(); i++)
        {
            uint16_t buffer = _keyboardMatrix.getLastData()[i];
            activateFromKeycode(buffer);
        }   
    }
    else deactivateAll();

    // Virtual switch reading //
    if (_modeSwitch.switchPress())
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
}

void Coordinator::activateFromKeycode(uint16_t keycode)
{
    switch (keycode)
    {
    case KeyCodes::KEY_ENCODER_0:
        _modeSwitch.activate();
        break;

    default:
        break;
    }
}

void Coordinator::deactivateAll(void)
{
    for (uint8_t i = 0; i < _virtualSwitchList.size(); i++) _virtualSwitchList[i]->deactivate();
}

void Coordinator::deactivateFromKeycode(uint16_t keycode)
{
    switch (keycode)
    {
    case KeyCodes::KEY_ENCODER_0:
        _modeSwitch.deactivate();
        break;

    default:
        break;
    }
}
