#include "KeyboardMatrix.h"

KeyboardData KeyboardMatrix::keypress(void)
{
    // Creates the reading variable that will be returned at the end of the function in the heap.
    static KeyboardData result;
    // Resets the variable for the upcoming iteration.
    result.reset();

    // for (uint8_t i = 0; i < _rowPins.pinCount(); i++)
    // {
    //     Serial.println(_rowPins[i]);
        
    //     // Writes a low voltage to a column.
    //     digitalWrite(_rowPins[i], LOW);
    //     // Adds a short delay to prevente false readings.
    //     //delayMicroseconds(1);
    //     // Stores the shift register's reading into the previously declared bool array.
    //     // Bool vector that reads the shift register.
    //     bool shiftRegisterReading[8] = { 0, 0, 1, 0, 1, 0, 0, 1 };

    //     // Reads the bool array.
    //     for (uint8_t j = 0; j < 8; j++)
    //     {
    //         // If a selected byte is true, stores the corresponding keypress into the result variable.
    //         if (shiftRegisterReading[j])
    //             Serial.println(indicesToKeystroke(i, j));
    //     }

    //     // Resets the state of the column pin.
    //     digitalWrite(_rowPins[i], HIGH);
    // }

    //---------------------------------//

    static unsigned long elapsedTime = millis();

    for (uint8_t i = 0; i < ROW_COUNT; i++)
    {
        digitalWrite(ROW_PINS[i], LOW);

        for (uint8_t j = 0; j < COL_COUNT; j++)
        {
            if (digitalRead(BASE_COL_PIN + j) == LOW)
            {
                if (millis() - elapsedTime > 100)
                {
                    Serial.println(KEYCODE_MATRIX[i][j]);
                    elapsedTime = millis();
                }
            }
        }
        digitalWrite(ROW_PINS[i], HIGH);
    }

    //---------------------------------//

    // Returns the pointer to the reading variable.
    return result;
}