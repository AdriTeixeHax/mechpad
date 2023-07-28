#include "KeyboardMatrix.h"

KeyboardReading* KeyboardMatrix::keypress(void)
{
    static KeyboardReading result;
    result.reset();

    for (uint i = 0; i < _colPins._pinCount; i++)
    {
        static bool* shiftRegisterReading = nullptr;

        digitalWrite(_colPins[i], LOW);
        shiftRegisterReading = charToBoolArray(_shiftRegister.reading());

        for (uint j = 0; j < 8; j++)
        {
            if (shiftRegisterReading[j])
            {
                result._numElem++;
                result._keypresses[result._numElem - 1] = indicesToKeystroke(i, j);
            }
        }
        
        delayMicroseconds(5);
    }

    return &result;
}