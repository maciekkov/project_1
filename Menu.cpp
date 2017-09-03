#include "Menu.h"

using namespace std;

Menu::Menu(string name = "WEATHER")
{
    _menuName = name;
    _wiersz.push_back(Wiersz("TIME", 1));
    _wiersz.push_back(Wiersz("DATE", 2));
    _wiersz.push_back(Wiersz("SENSOR", 3));
    _wiersz.push_back(Wiersz("SEND MAIL", 4));
    _wiersz.push_back(Wiersz("MAKE RAPORT", 5));
    _wiersz.push_back(Wiersz("EXIT", 6));
}
inline string Menu::getVectorName(int num)const
{
    return _wiersz[num].getWierszName();
}
inline string Menu::getMenuName()const
{
    return _menuName;
}
inline int Menu::getVectorID(int num)const
{
    return _wiersz[num].getNumID();
}
inline int Menu::getSizeVector()const
{
    return _wiersz.size();
}
