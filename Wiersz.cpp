#include "Wiersz.h"

using namespace std;

Wiersz::Wiersz(string name, int numID)
{
    _wierszName = name;
    _numID = numID;
}

string Wiersz::getWierszName()
{
    return _wierszName;
}

int Wiersz::getNumID()
{
    return _numID;
}
