#include "Coordinator.hpp"

#include <HID-Project.h>
#include <HID-Settings.h>

void Coordinator::loop(void)
{
    static ReadingData encoderReadingData = ReadingData(false, false);
    static bool encoderSwitchFlag = false;
    encoderReadingData = this->_rotaryEncoder.reading();

    if (encoderReadingData._hasBeenRotated)
    {
        if (!encoderReadingData._direction)
            Consumer.write(MEDIA_VOL_UP);
        else
            Consumer.write(MEDIA_VOL_DOWN);
    }

    if (_rotaryEncoder.switchUpdate() && _rotaryEncoder.getSwitchPressed())
    {
        Consumer.write(MEDIA_PLAY_PAUSE);
    }
}