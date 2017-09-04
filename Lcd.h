#ifndef LCD_H
#define LCD_H
#include <wiringPi.h>
#include <lcd.h>
#include <iostream>
#include <thread>

using namespace std;

class Lcd
{
public:
    Lcd();
    virtual ~Lcd(){}
    void writeOnScreen(uint32_t col, uint32_t position, const char* text);
    void writeOnScreenWithDelay(uint32_t col, uint32_t position, const char* text, uint32_t delay);
private:
    int _lcd;
};

#endif // LCD_H
