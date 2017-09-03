/*!
Klasa Menu ma za zadanie byc Opakowaniem dla klasy Wiersz.
*/
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Wiersz.h"
#include <vector>
#include <string>
using namespace std;

class Menu
{
public:
	Menu();
	Menu(string name);
	string getVectorName(int num)const;
	string getMenuName()const;
	int getVectorID(int num)const;
	int getSizeVector()const;
private:
	string _menuName;
	vector<Wiersz>_wiersz;
};

#endif //MENU_H
