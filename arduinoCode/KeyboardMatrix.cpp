#include "KeyboardMatrix.h"

KeyboardMatrix::KeyboardMatrix(bool hasShiftRegister, uint8_t SRPinLoad, uint8_t SRPinEnable, uint8_t SRPinData, uint8_t SRPinCLK) :
    _hasShiftRegister(hasShiftRegister), _shiftRegister(SRPinLoad, SRPinEnable, SRPinData, SRPinCLK), _lastData()
{
    if (!hasShiftRegister)
    {
        for (uint8_t i = 0; i < COL_COUNT; i++)
            pinMode(BASE_COL_PIN + i, INPUT);
    }

    for (uint8_t i = 0; i < ROW_COUNT; i++)
        pinMode(BASE_ROW_PIN + i, OUTPUT);
}

void KeyboardMatrix::keypress(void)
{
    static unsigned long elapsedTime = millis();

    _lastData.reset(); // Resets the struct where the read data will be stored for the next cycle.
    for (uint8_t i = 0; i < ROW_COUNT; i++) // For each row
    {
        digitalWrite(ROW_PINS[i], LOW); // writes a low state to the rows so that it can be read from the column pins or the shift register.
        
        if (!_hasShiftRegister) // If there is no shift register, reads the columns as they are based on its pins.
        {
            for (uint8_t j = 0; j < COL_COUNT; j++)
            {
                if (digitalRead(BASE_COL_PIN + j) == LOW) _lastData.addElem(KEYCODE_MATRIX[i][j]);
            }
        }
        else
        {
            _shiftRegister.reading();
            if (_shiftRegister.getLastValueByte() != 0)
            {
                for (uint8_t j = 0; j < COL_COUNT; j++)
                {
                    if (_shiftRegister.getLastValueBin()[j]) _lastData.addElem(KEYCODE_MATRIX[i][j]);
                }
            }
        }

        digitalWrite(ROW_PINS[i], HIGH);
    }
}