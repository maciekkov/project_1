#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include <thread>
#include <unistd.h>
#include "WeatherSensor.h"
#include "Lcd.h"
#include "GPIO.h"
#include "Menu.h"

#define SLEEP_2ms 2
#define SLEEP_5ms 3
#define SLEEP_1s 1
#define GOODBYE ((const char*)"GOODBYE")

class ControlSystem:public Lcd
{
public:
enum GpioNr {
    SET  = 4,
    UP   = 21,
    DOWN = 20
};
    ControlSystem();
    ~ControlSystem();
    void run();
    Menu _menu; 
    
private:
    void userSpace();
    int checkBotton(int num);
    int antyNois(int num);
    void execution(int numId);

	thread _user;
	
    WeatherSensor _sensor;
    GPIO _gpioSetBotton;
    GPIO _gpioUpBotton;
    GPIO _gpioDownBotton;
    
    
};

#endif // CONTROLSYSTEM_H

