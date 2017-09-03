#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include <thread>
#include <unistd.h>
#include "WeatherSensor.h"
#include "Lcd.h"
#include "Menu.h"
#include "GPIO.h"
#define SLEEP_2ms 2
#define SLEEP_5ms 5
#define SLEEP_1s 1

enum GpioNr {
    SET  = 4,
    UP   = 21,
    DOWN = 20
};

class ControlSystem:public Lcd, public Menu
{
public:
    ControlSystem();
    ~ControlSystem();
    void run();
private:
    void userSpace();
    void checkBotton(uint32_t num);
    int antyNois(int num);
    void execution(int numId);

    WeatherSensor _sensor;
    GPIO _gpioSetBotton;
    GPIO _gpioUpBotton;
    GPIO _gpioDownBotton;
    thread _user;
};

#endif // CONTROLSYSTEM_H

