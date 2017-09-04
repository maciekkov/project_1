#include "ControlSystem.h"

using namespace std;

ControlSystem::ControlSystem():_gpioSetBotton(SET), _gpioUpBotton(UP), _gpioDownBotton(DOWN) 
{
    _gpioSetBotton.initGpio("in");
    _gpioUpBotton.initGpio("in");
    _gpioDownBotton.initGpio("in");
     
}

void ControlSystem::run()
{
	
    _user = thread(&ControlSystem::userSpace, this);
    _sensor.runThreadCollectData();
}

int ControlSystem::checkBotton(int num)
{
    switch(num)
    {
    case SET:
    cout<< "set"<<endl;
        return _gpioSetBotton.GgetValue();
        break;
    case UP:
    cout<< "up"<<endl;
        return _gpioUpBotton.GgetValue();
        break;
    case DOWN:
        return _gpioDownBotton.GgetValue();
        break;
    default:
        cout << "Wrong gpio number" << endl;
    }
}

int ControlSystem::antyNois(int num)
{
    if(!checkBotton(num))
    {
        this_thread::sleep_for(chrono::microseconds(SLEEP_2ms));
        if(!checkBotton(num))
            return 0;
    }
    return 1;
}

void ControlSystem::userSpace()
{
    int num = 0;
    while(!_sensor.getThreadFlag())
    {
		this_thread::sleep_for(chrono::microseconds(SLEEP_5ms));;
        if(!checkBotton(UP))
        if(!antyNois(UP))
        {
			++num;
            if(num >= _menu.getSizeVector())
               num = 0;
            writeOnScreen(0, 5, _menu.getVectorName(num).c_str());
         }
         if(!checkBotton(DOWN))
         if(!antyNois(DOWN))
         {
            --num;
            if(num < 0)
               num = _menu.getSizeVector() - 1;
            writeOnScreen(0, 5, _menu.getVectorName(num).c_str());
         }
         if(!checkBotton(SET))
         {
            execution(_menu.getVectorID(num));
         }
     }
    writeOnScreen(0, 5, GOODBYE);
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
        writeOnScreenWithDelay(0, 0, _sensor.getCurrentParam().c_str(), SLEEP_1s);
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
    _user.join();
}
