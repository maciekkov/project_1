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
	Menu(const string& name = "WEATHER");
	virtual ~Menu(){}
	string getVectorName(int num);
	string getMenuName();
	int getVectorID(int num);
	int getSizeVector();
private:
	string _menuName;
	vector<Wiersz>_wiersz;
};

#endif //MENU_H
