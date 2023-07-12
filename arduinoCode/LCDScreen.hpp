#ifndef _LCDSCREEN__HPP_
#define _LCDSCREEN__HPP_

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Globals.hpp"

class LCDScreen
{
private:
    const uint _address;
    const uint _rows;
    const uint _columns;
    String _topLine;
    String _bottomLine;
    LiquidCrystal_I2C _screen;

public:
    /* CONSTRUCTOR */
    LCDScreen(int address, uint columns, uint rows) :
        _address(address),
        _rows(rows),
        _columns(columns),
        _topLine(""),
        _bottomLine(""),
        _screen(LiquidCrystal_I2C(_address, _columns, _rows))
    {
        _screen.init();
        _screen.backlight();
        this->print("Mechpad Project", "by AdriTeixeHax");
    }

    /* FUNCTIONS */
    void clear(void) { this->_screen.setCursor(0, 0); this->_screen.clear(); }

    void print(const String& topLine, const String& bottomLine)
    {
        _screen.clear();
        _screen.setCursor(0, 0);
        _screen.print(topLine);
        _screen.setCursor(0, 1);
        _screen.print(bottomLine);
    }

    void print(bool topLine, uint bottomLine)
    {
        _screen.clear();
        _screen.setCursor(0, 0);
        _screen.print(topLine);
        _screen.setCursor(0, 1);
        _screen.print(bottomLine);
    }

    void print(const String& message, int column, int row)
    {
        _screen.clear();
        _screen.setCursor(column, row);
        _screen.print(message);
    }

    void printOnce(const String& topLine, const String& bottomLine)
    {
        if (topLine == _topLine && bottomLine == _bottomLine) return;
        else
        {
            _topLine    = topLine;
            _bottomLine = bottomLine;

            this->print(topLine, bottomLine);
        }
    }
};

#endif