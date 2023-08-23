#include "Coordinator.h"

#include <HID-Project.h>
#include <HID-Settings.h>

Coordinator::Coordinator(void) :
    _machineState(MachineState::startup),
    _stripConfigState(StripConfigState::brightness),
    _LCDScreen(0x27, 16, 2),
    _rotaryEncoder(ENCODER_PIN_A, ENCODER_PIN_B),
    _RGBStrip(STRIP_PIN, 6, 4),
    _keyboardMatrix(SR_PIN_LOAD, SR_PIN_EN, SR_PIN_DATA, SR_PIN_CLK),
    _modeSwitching()
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
            //_rotaryEncoder.resetTimePressed();
            _machineState = MachineState::running;
            elapsedTime = millis();
        }
        break;

    case MachineState::running:
        if (_modeSwitching.switchLongPress())
        {
            _modeSwitching.resetTimePressed();
            _machineState = MachineState::stripConfig;
        }
        break;

    case MachineState::stripConfig:
        if (_modeSwitching.switchLongPress())
        {
            _modeSwitching.resetTimePressed();
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

    // Virtual switch reading //
    if (_modeSwitching.switchPress())
        Consumer.write(MEDIA_PLAY_PAUSE);

    // Keyboard matrix reading //
    _keyboardMatrix.keypress();
    static uint16_t buffer = 0;
    if (_keyboardMatrix.getLastData().size() != 0)
    {
        for (uint8_t i = 0; i < _keyboardMatrix.getLastData().size(); i++)
        {
            buffer = _keyboardMatrix.getLastData()[i];

            if (_keyboardMatrix.getLastData()[i] < KeyCodes::THRESHOLD)
                Keyboard.press(static_cast<KeyboardKeycode>(_keyboardMatrix.getLastData()[i]));
            else 
                _modeSwitching.activate(); /*activateFromKeycode(_keyboardMatrix.getLastData()[i])*/;
        }
    }
    else
    {
        Keyboard.release(static_cast<KeyboardKeycode>(buffer));
        _modeSwitching.deactivate();
    }
       
}

void Coordinator::stripConfig(void)
{
    Serial.println("Strip config.");
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

    // Keyboard matrix reading //
    _keyboardMatrix.keypress();
    if (_keyboardMatrix.getLastData().size() != 0)
    {
        for (uint8_t i = 0; i < _keyboardMatrix.getLastData().size(); i++)
        {
            if (_keyboardMatrix.getLastData()[i] == KeyCodes::KEY_ENCODER_0)
                _modeSwitching.activate();
        }
    }
    else
    {
        _modeSwitching.deactivate();
    }

    // Virtual switch reading //
    if (_modeSwitching.switchPress())
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
        _modeSwitching.activate();
        break;

    default:
        break;
    }
}

void Coordinator::deactivateFromKeycode(uint16_t keycode)
{
    switch (keycode)
    {
    case KeyCodes::KEY_ENCODER_0:
        _modeSwitching.deactivate();
        break;

    default:
        break;
    }
}
