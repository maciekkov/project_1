#include <sstream>
#include "DateTime.h"

using namespace std;

DateTime::DateTime()
{
    _now = time(NULL);
    _t = localtime(&_now);
}

int DateTime::getSeconds()const
{
    return _t->tm_sec;
}

int DateTime::getMinuts()const
{
    return _t->tm_min;
}

int DateTime::getHours()const
{
    return _t->tm_hour;
}

int DateTime::getDays()const
{
    return _t->tm_mday;
}

inline int DateTime::getMonths()const
{
    return _t->tm_mon;
}

int DateTime::getYear()const
{
    return _t->tm_year + YEARS;
}

inline int DateTime::getTimeticks()const
{
    return (int) _now;
}

void DateTime::refreash()
{
    _now = time(0);
    _t = localtime(&_now);
}

string DateTime::getTime()
{
    refreash();
    string bufor;
    bufor = toString(getHours()) + ":" + toString(getMinuts()) + ":" + toString(getSeconds());
    return bufor;
}

string DateTime::getDate()
{
    refreash();
    string bufor;
    bufor = toString(getDays()) + ":" + toString(getMonths()) + ":" + toString(getYear());
    return bufor;
}

string DateTime::toString(int num)const
{
    stringstream ss;
    ss << num;
    return ss.str();
}

ostream& DateTime::logUpdate(const string& text, const char* fileName)
{
    _f.open(fileName, ios::app);
    if(_f.good())
    {
        _f << "[ " + getDate() + " " + getTime() + "] -> " + text << endl;
        _f.close();
    }
    else
    {
        perror("Couldn't open file to write log");
    }
}
