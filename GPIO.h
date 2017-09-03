/*!
Klasa, która zapewnia obs³ugê GPIO poprzez interfejs u¿ytkownika
*/
#ifndef GPIO_H
#define GPIO_H

#include <string>
#include <fstream>
#include <fcntl.h>
#include <sstream>
#include <stdlib.h>
#include <poll.h>
#include <string.h>
#include <stdio.h>

using namespace std;

#define RDBUF_LEN 5

class GPIO
{
public:
    GPIO();
    GPIO(const unsigned int gpioNum);
    GPIO(const string& gpioNum):_gpioNum(gpioNum){}
    virtual ~GPIO()

    void initGpio(const string& data);
/*!
Zestaw API do odczytu/zapisu interfejsu u¿ytkownika wystawionego przez Kernel
*/

    int Gexport()const;
    int Gdirection(const string& data)const;
    int GsetValue(unsigned int num)const;
    int GsetEdge(const string& mode)const;
    int GgetValue()const;
    int Gunexport()const;

private:
    string toString(unsigned int num)const;
    int openFile(const string& path, unsigned int mode, const string& data)const;

  const string _gpioNum;
};

#endif // GPIO_H
