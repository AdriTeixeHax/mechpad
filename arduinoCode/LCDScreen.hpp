#ifndef _LCDSCREEN__HPP_
#define _LCDSCREEN__HPP_

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Globals.hpp"

class LCDScreen
{
private:
    const uint16_t _address;
    const uint8_t  _rows;
    const uint8_t  _columns;
    LiquidCrystal_I2C _screen;

    uint8_t _numBuffer;
    string  _strBuffer1;
    string  _strBuffer2;

public:
    /* CONSTRUCTOR */
    LCDScreen(uint16_t address, uint8_t columns, uint8_t rows) :
        _address(address),
        _rows(rows),
        _columns(columns),
        _screen(LiquidCrystal_I2C(_address, _columns, _rows)),
        _numBuffer(0),
        _strBuffer1(""),
        _strBuffer2("")
    {
        _screen.init();
        _screen.backlight();
        this->printOnce("Mechpad Project", "by AdriTeixeHax");
    }

    /* FUNCTIONS */
    void clear(void)
    {
        _screen.setCursor(0, 0);
        _screen.clear();
        _numBuffer = 0;
        _strBuffer1 = "";
        _strBuffer2 = "";
    }

    void print(string topLine, string bottomLine)
    {
        _screen.clear();
        _screen.setCursor(0, 0);
        _screen.print(topLine);
        _screen.setCursor(0, 1);
        _screen.print(bottomLine); 
    }

    void print(string topLine, uint8_t bottomLine)
    {
        _screen.clear();
        _screen.setCursor(0, 0);
        _screen.print(topLine);
        _screen.setCursor(0, 1);
        _screen.print(bottomLine); 
    }

    void printOnce(string topLine, string bottomLine)
    {
        if (_strBuffer1 == topLine && _strBuffer2 == bottomLine) return;
        
        this->print(topLine, bottomLine);

        _strBuffer1 = topLine;
        _strBuffer2 = bottomLine;
    }

    void printOnce(string topLine, uint8_t bottomLine)
    {
        if (_strBuffer1 == topLine && _numBuffer == bottomLine) return;
        
        this->print(topLine, bottomLine);

        _strBuffer1 = topLine;
        _numBuffer  = bottomLine;
    }
};

#endif