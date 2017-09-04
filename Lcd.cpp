#include "Lcd.h"

using namespace std;

Lcd::Lcd()
{
    
    _lcd = lcdInit (2, 16, 4, 3, 0, 6, 1, 5, 4, 0, 0 ,0, 0);
}

void Lcd::writeOnScreen(uint32_t col, uint32_t position, const char* text)
{
	lcdClear(_lcd);
	lcdPosition(_lcd, position, col);
	lcdPuts(_lcd, text);
}

void Lcd::writeOnScreenWithDelay(uint32_t col, uint32_t position, const char* text, uint32_t delay)
{
    lcdClear(_lcd);
	lcdPosition(_lcd, position, col);
	lcdPuts(_lcd, text);
	this_thread::sleep_for(chrono::seconds(delay));
}
