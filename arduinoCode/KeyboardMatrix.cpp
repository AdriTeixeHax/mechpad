#include "KeyboardMatrix.h"

void KeyboardMatrix::keypress(void)
{
    static unsigned long elapsedTime = millis();
    if (millis() - elapsedTime > 0)
    {
        _lastData.reset();
        for (uint8_t i = 0; i < ROW_COUNT; i++)
        {
            digitalWrite(ROW_PINS[i], LOW);
            for (uint8_t j = 0; j < COL_COUNT; j++)
            {
                if (digitalRead(BASE_COL_PIN + j) == LOW)
                {
                    _lastData.addElem(KEYCODE_MATRIX[i][j]);
                    elapsedTime = millis();
                }
            }
            digitalWrite(ROW_PINS[i], HIGH);
        }
    }
}