/*!
Klasa DateTime jest odpowiedzialna za tworzenie logów oraz zarz¹dzanie czasem.
*/
#ifndef DATETIME_H
#define DATETIME_H

#include <fstream>
#include <string>

using namespace std;
/*!
 YEARS to parametr jaki nale¿y dodaæ do parametru roku ze struktury _t aby otrzymaæ poprawny rok.
*/
#define YEARS 1900

class DateTime
{
public:
    DateTime();
    virtual ~DateTime(){}
/*!
Zestaw fukncji daj¹cych nam czêœci daty i czasu do dyspozycji.
*/
    int getSeconds()const;
    int getMinuts()const;
    int getHours()const;
    int getDays()const;
    int getMonths()const;
    int getYear()const;
    int getTimeticks()const;
/*!
GetTime() zwraca jako string kompletn¹ godzinê w Formacie HH:MM:SS
GetDate() zwraca jako string kompletn¹ datê w formacie DD:MM:YY
*/
    string getTime();
    string getDate();
/*!
 logUpdate() Dziêki tej funkcji tworzymy ró¿nego rodzaju logFile b¹dŸ aktualizujemy ju¿ istiej¹ce.
*/
    ostream& logUpdate(const string& text, const char* fileName);
private:
/*!
 refreash()odœwie¿a strukturê przechowywuj¹c¹ czas
*/
    void refreash();
    string toString(int num)const;

    ofstream _f;
    time_t _now;
/*!
 zmienna _t to struktura przechowywuj¹ca czas.
*/
    struct tm* _t;
};
#endif
