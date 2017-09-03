#include <sstream>
#include "DateTime.h"

using namespace std;

DateTime::DateTime()
{
    _now = time(NULL);
    _t = localtime(&now);
}

inline int DateTime::getSeconds()const
{
    return _t->tm_sec;
}

inline int DateTime::getMinuts()const
{
    return _t->tm_min;
}

inline int DateTime::getHours()const
{
    return _t->tm_hour;
}

inline int DateTime::getDays()const
{
    return _t->tm_mday;
}

inline int DateTime::getMonths()const
{
    return _t->tm_mon;
}

inline int DateTime::getYear()const
{
    return _t->tm_year + YEARS;
}

inline int DateTime::getTimeticks()const
{
    return (int) now;
}

inline void DateTime::refreash()
{
    _now = time(0);
    _t = localtime(&now);
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
    f.open(fileName, ios::app);
    if(f.good())
    {
        f << "[ " + getDate() + " " + getTime() + "] -> " + text << endl;
        f.close();
    }
    else
    {
        perror("Couldn't open file to write log");
    }
}
