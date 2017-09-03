/*!
Klasa WeatherSensor ma za zadanie zbiera� dan� z czujnika BME280 oraz udost�pnia� API
do raportowania i odczytywania temperatury, ci�nienia i wilgotno�ci.
*/
#ifndef WEATHERSENSOR_H_
#define WEATHERSENSOR_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include "BME280.h"
#include "DateTime.h"

using namespace std;

/*!
FREQUENCY_TIME_RAPORT okre�la co ile minut ma zosta� zapisany stan temperatury
*/
#define FREQUENCY_TIME_RAPORT 59
/*!
Okresy czasu w sekundach
*/
#define HOUR 3600
#define DAY 86400

#define ROW 60;
#define COL 24;

#define LOG_FILE_DAILY ((const char*)"logFileDaily.txt")
#define LOG_FILE_INSTANT ((const char*)"logFileInstant.txt")

class  WeatherSensor:public BME280, public BusyWaitThreadInterface
{
public:
    WeatherSensor();
    ~WeatherSensor();
/*!
runThreadCollectData() ma za zadanie uruchomi�  w�tek w kt�rym b�d� odczytywane i aktualizowane dane z czujnika BME280.
Dane temperatury, ci�nienia i wilgotno�ci b�d� zapisywane w vectorze _secRaport jako tuple tych 3 warto�ci.
*/
    TStatus runThreadCollectData() override;
    TStatus stopThreadCollectData() override;
    string getAvg(const vector<tuple<double, int, int> >& date, int num)const;
	string getDataForEachHour(int i)const;
	string getCurrentParam()const;
    void make24HRaport()const;
    void makeRaportNow()const;
    void mailRaport()const;
/*!
printSchema() Tworzy wykres graficzny na, kt�rym mo�na zaobserwowa� zmiany temperatury.
*/
	void printSchema();
    DateTime log;
private:
/*!
collectData() zbiera dane i zapisuje je co sekunde w wektorze _secRaport oraz co godzin� w w wektorze _hourRaport.
*/
    void collectData();
    bool countTime(const time_t t, int option);
/*!
co 24 godziny czy�ci wektory
*/
    void resetVecotrs();
    string toString(float num);

/*!
_startHour i _startDay rozpoczynaj� mierzenie czasu po uruchomieniu czujnika i s� wykorzystywane do �ledzenia czasu i wykonywania okresowych raport�w.
*/
    time_t _startHour;
    time_t _startDay;
/*!
_tab to zmienna 2 wymiarowej tablicy przechowuwuj�ca graficzn� reprezentacj� zmiany temperatury.
*/
    char** _tab;
    vector<tuple<double, int, int> >_secRaport;
	vector<tuple<double, int, int> >_hourRaport;
};

#endif //WEATHERSENSOR_H_
