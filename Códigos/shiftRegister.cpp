#include <Arduino.h>

#define SR_LOAD 7
#define SR_CLK_ENABLE 4
#define SR_DATA_IN 5
#define SR_CLK_IN 6

bool explode_byte(byte b)
{
    bool bit_return[8];
    for (int i = 0; i < 8; i++)
    {
        bit_return[i] = bitRead(b, i);
    }
    return bit_return;
}

void shift_register_setup(void)
{
    pinMode(SR_LOAD,       OUTPUT);
    pinMode(SR_CLK_ENABLE, OUTPUT);
    pinMode(SR_CLK_IN,     OUTPUT);
    pinMode(SR_DATA_IN,    INPUT);
}

bool shift_register_reading(void)
{
    bool reading[8];
    // Writes a pulse to the load pin to load the input values into the shift register.
    digitalWrite(SR_LOAD, LOW);
    delayMicroseconds(5);
    digitalWrite(SR_LOAD, HIGH);
    delayMicroseconds(5);

    // Gets the byte data from the shift register and turns it to an 8 bit bool vector.
    digitalWrite(SR_CLK_IN,     HIGH);
    digitalWrite(SR_CLK_ENABLE, LOW);
    byte byte_reading = shiftIn(SR_DATA_IN, SR_CLK_IN, LSBFIRST);
    digitalWrite(SR_CLK_ENABLE, HIGH);
    reading = explode_byte(byte_reading);

    return reading;
}