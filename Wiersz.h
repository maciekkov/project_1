/*!
Klasa przechowywująca numer porządkowy oraz nazwę która jest reprezentacją jakiejś funkcji wyświetlana na wyświetlaczu.
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
