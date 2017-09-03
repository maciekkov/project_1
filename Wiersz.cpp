#include "Wiersz.h"

using namespace std;

Wiersz::Wiersz(string name, int numID)
{
    _wierszName = name;
    _numID = numID;
}
inline string getWierszName()const
{
    return _wierszName;
}
inline int getNumID()const
{
    return _numID;
}
