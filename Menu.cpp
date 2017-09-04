#include "Menu.h"

using namespace std;

Menu::Menu(const string& name)
{
    _menuName = name;
    _wiersz.push_back(Wiersz("TIME", 1));
    _wiersz.push_back(Wiersz("DATE", 2));
    _wiersz.push_back(Wiersz("SENSOR", 3));
    _wiersz.push_back(Wiersz("SEND MAIL", 4));
    _wiersz.push_back(Wiersz("MAKE RAPORT", 5));
    _wiersz.push_back(Wiersz("EXIT", 6));
}

string Menu::getVectorName(int num)
{
    return _wiersz[num].getWierszName();
}

string Menu::getMenuName()
{
    return _menuName;
}

int Menu::getVectorID(int num)
{
    return _wiersz[num].getNumID();
}

int Menu::getSizeVector()
{
    return _wiersz.size();
}
