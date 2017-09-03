#include "ControlSystem.h"

ControlSystem::ControlSystem():_gpioSetBotton(SET), _gpioUpBotton(UP), _gpioDownBotton(DOWN)
{
    _gpioSetBotton.initGpio("in");
    _gpioUpBotton.initGpio("in");
    _gpioDownBotton.initGpio("in");
    _isExit = false;
}

void ControlSystem::run()
{
    user = thread(&ControlSystem::userSpace, this);
    _sensor.runThreadCollectData();
}

int ControlSystem::checkBotton(uint32_t num)
{
    switch(num)
    {
    case SET:
        return _gpioSetBotton.GgetValue();
        break;
    case UP:
        return _gpioUpBotton.GgetValue();
        break;
    case DOWN:
        return _gpioDownBotton.GgetValue();
        break;
    default:
        cout << "Wrong gpio number" << endl;
    }
}

int ControlSystem::antyNois(uint32_t pin)
{
    if(checkBotton(pin))
    {
        this_thread::sleep_for(chrono::microseconds(SLEEP_2ms));
        if(checkBotton(pin))
            return 0;
    }
    return 1;
}

void ControlSystem::userSpace( )
{
    int num = 0;
    while(1)
    {
        if(checkBotton(SET))
            if(!antyNois(SET))
            {
                writeOnScreenWithDelay(0, 0, menu.menuName().c_str(), SLEEP_1s);
                while(1)
                {
                    this_thread::sleep_for(chrono::microseconds(SLEEP_5ms));;
                    if(checkBotton(UP))
                        if(!antyNois(UP))
                        {
                            ++num;
                            if(num >= menu.getSizeVector())
                                num = 0;
                            writeOnScreen(0, 5, menu.getVectorName(num));
                        }
                    if(checkBotton(DOWN))
                        if(!antyNois(DOWN))
                        {
                            --num;
                            if(num < 0)
                                num = menu.getSizeVector() - 1;
                            writeOnScreen(0, 5, menu.getVectorName(num));
                        }
                    if(checkBotton(SET))
                    {
                        execution(menu.getVectorID(num));
                    }
                }
            }
    }
}

void ControlSystem::execution(int numID)
{
    switch(numID)
    {
    case 1:
        writeOnScreenWithDelay(0, 5, _sensor.log.getTime().c_str(), SLEEP_1s);
        break;
    case 2:
        writeOnScreenWithDelay(0, 5, _sensor.log.getDate().c_str(), SLEEP_1s);
        break;
    case 3:
        writeOnScreenWithDelay(0, 0, _sensor.getCurrentParam());
        break;
    case 4:
        _sensor.mailRaport();
        break;
    case 5:
        _sensor.makeRaportNow();
        _sensor.printSchema();
        break;
    case 6:
        _sensor.stopThreadCollectData();
        break;
    default:
        break;
    }
}

ControlSystem::~ControlSystem()
{
    user.join();
}
