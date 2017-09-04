/*!
Klasa przechowywuj¹ca numer porz¹dkowy oraz nazwê która jest reprezentacj¹ jakiejœ funkcji wyœwietlana na wyœwietlaczu.
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
