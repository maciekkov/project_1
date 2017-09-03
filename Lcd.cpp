#include "Lcd.h"

LCD::Lcd()
{
    wiringPiSetup();
    _lcd = lcdInit (2, 16, 4, 3, 0, 6, 1, 5, 4, 0, 0 ,0, 0);
}

void Lcd::writeOnScreen(uint32_t col, uint32_t position, const char* text)
{
	lcdClear(lcd);
	lcdPosition(lcd, position, col);
	lcdPuts(lcd, text);
}

void Lcd::writeOnScreenWithDelay(uint32_t col, uint32_t position, const char* text, uint32_t delay)
{
    lcdClear(lcd);
	lcdPosition(lcd, position, col);
	lcdPuts(lcd, text);
	this_thread::sleep_for(chrono::seconds(delay));
}
