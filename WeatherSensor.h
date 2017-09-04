/*!
Klasa WeatherSensor ma za zadanie zbieraæ danê z czujnika BME280 oraz udostêpniaæ API
do raportowania i odczytywania temperatury, ciœnienia i wilgotnoœci.
*/
#ifndef WEATHERSENSOR_H_
#define WEATHERSENSOR_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include "BME280.h"
#include "DateTime.h"
#include "BusyWaitThreadInterface.h"

using namespace std;

/*!
FREQUENCY_TIME_RAPORT okreœla co ile minut ma zostaæ zapisany stan temperatury
*/
#define FREQUENCY_TIME_RAPORT 59
/*!
Okresy czasu w sekundach
*/
#define HOUR 3600
#define DAY 86400

#define ROW 60
#define COL 24

#define LOG_FILE_DAILY ((const char*)"logFileDaily.txt")
#define LOG_FILE_INSTANT ((const char*)"logFileInstant.txt")

class  WeatherSensor:public BME280, public BusyWaitThreadInterface
{
public:
    WeatherSensor();
    ~WeatherSensor();
/*!
runThreadCollectData() ma za zadanie uruchomiæ  w¹tek w którym bêd¹ odczytywane i aktualizowane dane z czujnika BME280.
Dane temperatury, ciœnienia i wilgotnoœci bêd¹ zapisywane w vectorze _secRaport jako tuple tych 3 wartoœci.
*/
    int runThreadCollectData() override;
    int stopThreadCollectData() override;
    string getAvg(const vector<tuple<double, int, int> >& date, int num);
	string getDataForEachHour(int i);
	string getCurrentParam();
    void make24HRaport();
    void makeRaportNow();
    void mailRaport();
    bool getThreadFlag();
/*!
printSchema() Tworzy wykres graficzny na, którym mo¿na zaobserwowaæ zmiany temperatury.
*/
	void printSchema();
    DateTime log;
private:
/*!
collectData() zbiera dane i zapisuje je co sekunde w wektorze _secRaport oraz co godzinê w w wektorze _hourRaport.
*/
    void collectData();
    bool countTime(const time_t t, int option);
/*!
co 24 godziny czyœci wektory
*/
    void resetVecotrs();
    string toString(float num)const;

/*!
_startHour i _startDay rozpoczynaj¹ mierzenie czasu po uruchomieniu czujnika i s¹ wykorzystywane do œledzenia czasu i wykonywania okresowych raportów.
*/
    time_t _startHour;
    time_t _startDay;
/*!
_tab to zmienna 2 wymiarowej tablicy przechowuwuj¹ca graficzn¹ reprezentacjê zmiany temperatury.
*/
    char** _tab;
    vector<tuple<double, int, int> >_secRaport;
	vector<tuple<double, int, int> >_hourRaport;
};

#endif //WEATHERSENSOR_H_
