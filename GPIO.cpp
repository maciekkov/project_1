#include "GPIO.h"

#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

enum mode
{
    WRITE  = 1,
    READ = 2
};

GPIO::GPIO(const unsigned int gpioNum):_gpioNum{toString(gpioNum)}
{

}

GPIO::~GPIO()
{
    //dtor
}

void GPIO::initGpio(const string& data)const
{
    Gexport();
    Gdirection(data);
}

int GPIO::Gexport()const
{
    string path = "/export";
    if(openFile(path, WRITE, _gpioNum) < 0)
    {
        perror("error export");
        return -1;
    }
    return 1;
}

int GPIO::Gdirection(const string& data)const
{
    string path = "/gpio" + _gpioNum + "/direction";
    if(openFile(path, WRITE, data) < 0)
    {
        perror("error direction");
        return -1;
    }
    return 1;
}

int GPIO::GsetValue(int num)const
{
    string path = "/gpio" + _gpioNum + "/value";
    if(openFile(path, WRITE, toString(num)) < 0)
    {
        perror("error value");
        return -1;
    }
    return 1;
}

int GPIO::GsetEdge(const string& type)const
{
    string path = "/gpio" + _gpioNum + "/edge";
    if(openFile(path, WRITE, type) < 0)
    {
        perror("error value");
        return -1;
    }
    return 1;
}

int GPIO::GgetValue()const
{
    string path = "/gpio" + _gpioNum + "/value";
    int value = 0;
    value = openFile(path, READ);
    if(value < 0)
    {
        perror("error value");
        return -1;
    }
    return value;
}

int GPIO::Gunexport()const
{
    string path = "/unexport";
    if(openFile(path, WRITE, _gpioNum) < 0)
    {
        perror("error unexport");
        return -1;
    }
    return 1;
}

string GPIO::toString(unsigned int num)const
{
    string bufor;
    stringstream ss;
    ss << num;
    return ss.str();
}

int GPIO::openFile(const string& path, unsigned int modee, const string& data = "")const
{
    fstream fd;
    string value;
    string bufor = "/sys/class/gpio" + path;
    fd.open(bufor.c_str());
    if(fd.fail())
    {
        perror("couldn't open file");
        return -1;
    }

    switch(modee)
    {
    case 1:
        fd << data;
        fd.close();
        return 1;
    case 2:
        fd >> value;
        fd.close();
        int intbufor = atoi(value.c_str());
        if(intbufor == 0)
            return 0;
        else
            return 1;
    }
}
