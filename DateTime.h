/*!
Klasa DateTime jest odpowiedzialna za tworzenie log�w oraz zarz�dzanie czasem.
*/
#ifndef DATETIME_H
#define DATETIME_H

#include <fstream>
#include <string>

using namespace std;
/*!
 YEARS to parametr jaki nale�y doda� do parametru roku ze struktury _t aby otrzyma� poprawny rok.
*/
#define YEARS 1900

class DateTime
{
public:
    DateTime();
    virtual ~DateTime(){}
/*!
Zestaw fukncji daj�cych nam cz�ci daty i czasu do dyspozycji.
*/
    int getSeconds()const;
    int getMinuts()const;
    int getHours()const;
    int getDays()const;
    int getMonths()const;
    int getYear()const;
    int getTimeticks()const;
/*!
GetTime() zwraca jako string kompletn� godzin� w Formacie HH:MM:SS
GetDate() zwraca jako string kompletn� dat� w formacie DD:MM:YY
*/
    string getTime();
    string getDate();
/*!
 logUpdate() Dzi�ki tej funkcji tworzymy r�nego rodzaju logFile b�d� aktualizujemy ju� istiej�ce.
*/
    ostream& logUpdate(const string& text, const char* fileName);
private:
/*!
 refreash()od�wie�a struktur� przechowywuj�c� czas
*/
    void refreash();
    string toString(int num)const;

    ofstream _f;
    time_t _now;
/*!
 zmienna _t to struktura przechowywuj�ca czas.
*/
    struct tm* _t;
};
#endif
