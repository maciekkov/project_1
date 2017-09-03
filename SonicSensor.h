#ifndef SONICSENSOR_H
#define SONICSENSOR_H
#include "GPIO.h"

#define MAX_RANGE 200
class SonicSensor
{
public:
    SonicSensor(int gpioT,gpioE):_gpioEcho{gpioNum},_gpioEcho{gpioE}{}
    ~SonicSensor();
    uint32_t getRange();
    void initSensor();

private:
    uint32_t range;
    uint32_t maxRange{MAX_RANGE};
    Gpio _gpioTrigger;
    Gpio _gpioEcho;
};
//MF: to ponizej wgl dziala? Bo raczej nie powinno... Plus definicje w header... Do cpp z tym.
void initSensor()
{
     _gpioTrigger.initGpio("in");
     _gpioEcho.initGpio("out");
}
 uint32_t SonicSensor::getRange()
 {
    _gpioTrigger.Gdirection("out");
    this_thread::sleep_for(chrono::nanoseconds(2));

    _gpioTrigger.Gdirection("in");
    this_thread::sleep_for(chrono::nanoseconds(10));
    _gpioTrigger.Gdirection("out");


    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Hello World\n";
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

 }
#endif // SONICSENSOR_H
