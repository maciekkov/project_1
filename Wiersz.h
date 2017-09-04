/*!
Klasa przechowywuj�ca numer porz�dkowy oraz nazw� kt�ra jest reprezentacj� jakiej� funkcji wy�wietlana na wy�wietlaczu.
*/
#ifndef WIERSZ_H
#define WIERSZ_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Wiersz
{
public:
	Wiersz(){}
	Wiersz(string name, int numID);
	string getWierszName();
	int getNumID();
private:
	string _wierszName;
	int _numID;
};
#endif //WIERSZ_H
