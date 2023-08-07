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

public:
    /* CONSTRUCTOR */
    LCDScreen(uint16_t address, uint8_t columns, uint8_t rows) :
        _address(address),
        _rows(rows),
        _columns(columns),
        _screen(LiquidCrystal_I2C(_address, _columns, _rows))
    {
        _screen.init();
        _screen.backlight();
        this->printOnce("Mechpad Project", "by AdriTeixeHax");
    }

    /* FUNCTIONS */
    void clear(void) { this->_screen.setCursor(0, 0); this->_screen.clear(); }

    void print(string topLine, string bottomLine)
    {
        _screen.clear();
        _screen.setCursor(0, 0);
        _screen.print(topLine);
        _screen.setCursor(0, 1);
        _screen.print(bottomLine); 
    }

    void print(string message, int column, int row)
    {
        _screen.clear();
        _screen.setCursor(column, row);
        _screen.print(message);
    }

    void printOnce(string message, int column, int row)
    {
        static string temp = "";
        if (temp == message) return;
        this->print(message, column, row);
        temp = message;
    }

    void printOnce(string topLine, string bottomLine)
    {
        static string tempTop = "";
        static string tempBot = "";
        if (tempTop == topLine && tempBot == bottomLine) return;
        
        this->print(topLine, bottomLine);

        tempTop = topLine;
        tempBot = bottomLine;
    }
};

#endif