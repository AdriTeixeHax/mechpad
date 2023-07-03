#include "Coordinator.hpp"

#include <HID-Project.h>
#include <HID-Settings.h>

void Coordinator::loop(void)
{
    ReadingData encoderReadingData = this->_rotaryEncoder.reading();
    if (encoderReadingData._hasBeenRotated)
    {
        if (encoderReadingData._direction)
            Consumer.write(MEDIA_VOL_UP);
        else
            Consumer.write(MEDIA_VOL_DOWN);
    }
    if (_rotaryEncoder.switchUpdate())
    {
        if (_rotaryEncoder.getSwitchPressed())
            Consumer.write(MEDIA_PLAY_PAUSE);
    }
}