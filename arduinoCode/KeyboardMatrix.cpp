#include "KeyboardMatrix.h"

KeyboardData* KeyboardMatrix::keypress(void)
{
    // Creates the reading variable that will be returned at the end of the function in the heap.
    static KeyboardData result;
    // Resets the variable for the upcoming iteration.
    result.reset();

    for (uint8_t i = 0; i < _colPins._pinCount; i++)
    {
        // Bool vector that reads the shift register.
        static bool* shiftRegisterReading = nullptr;

        // Writes a low voltage to a column.
        digitalWrite(_colPins[i], LOW);
        // Adds a short delay to prevente false readings.
        delayMicroseconds(5);
        // Stores the shift register's reading into the previously declared bool array.
        shiftRegisterReading = charToBoolArray(_shiftRegister.reading());

        // Reads the bool array.
        for (uint8_t j = 0; j < 8; j++)
        {
            // If a selected byte is true, stores the corresponding keypress into the result variable.
            if (shiftRegisterReading[j])
                result.addElem(indicesToKeystroke(i, j));
        }

        // Resets the state of the column pin.
        digitalWrite(_colPins[i], HIGH);
    }

    // Returns the pointer to the reading variable.
    return &result;
}