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
    virtual ~GPIO();

    void initGpio(const string& data);
/*!
Zestaw API do odczytu/zapisu interfejsu u¿ytkownika wystawionego przez Kernel
*/

    int Gexport();
    int Gdirection(const string& data);
    int GsetValue(unsigned int num);
    int GsetEdge(const string& mode);
    int GgetValue();
    int Gunexport();

private:
    string toString(unsigned int num);
    int openFile(const string& path, unsigned int mode, const string& data);

	string _gpioNum;
};

#endif // GPIO_H
