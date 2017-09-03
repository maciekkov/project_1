#include <fstream>
#include "WeatherSensor.h"

using namespace std;
_flag24Hours
WeatherSensor::WeatherSensor()
{
    _hourRaport.resize(COL);
    _startHour = time(NULL);
    _startDay = time(NULL);

    _tab = new char* [ROW];
    for(uint32_t i = 0; i < ROW; ++i)
        _tab[i] = new char[COL];
}

WeatherSensor::~WeatherSensor()
{
    for(uint32_t i = 0; i < ROW; ++i)
        delete[] _tab[i];
    delete[] _tab;
}

TStatus WeatherSensor::runThreadCollectData() override
{
   _thread = thread(&WeatherSensor::collectData, this);
   return TStatus OK;
}

TStatus stopThreadCollectData() override
{
    _stopThread = true;
    return TStatus OK;
}

string WeatherSensor::getAvg(const vector<tuple<double, int, int> >& data, int num)const
{
    double tsuma = 0, hsuma = 0, psuma = 0;
    for(uint i = data.size(); i > 0; --i)
    {
        tsuma += get<0>(data[i]);
        hsuma += get<1>(data[i]);
        psuma += get<2>(data[i]);
    }
    double avrT = tsuma/num;
    double avrH = hsuma/num;
    double avrP = psuma/num;
    string buffor = "Temperatura:" + toString(avrT) + " HUmadity:" + toString(avrH) + " Pressure:" + toString(avrP);
    return buffor;
}

string WeatherSensor::getDataForEachHour(int i)const
{
    double	  tsuma = get<0>(_HourRaport[i]);
    double	  hsuma = get<1>(_HourRaport[i]);
    double	  psuma = get<2>(_HourRaport[i]);

    string buffor = "Temp:" + toString(tsuma)+"     Hum:" + toString(hsuma) + " Press:" + toString(psuma);
    return buffor;
}

string WeatherSensor::getCurrentParam()const
{
    double	  tsuma = get<0>(_secRaport.back());
    double	  hsuma = get<1>(_secRaport.back());
    double	  psuma = get<2>(_secRaport.back());

    string buffor = "Temp: " + toString(tsuma) + "     Hum:" + toString(hsuma) + " Press:" + toString(psuma);
    return buffor;
}

void WeatherSensor::make24HRaport()const
{
    string bufor;
    for(uint i = 0; i <_HourRaport.size(); ++i)
    {
        bufor = getDataForEachHour(i);
        log.logUpdate(bufor, LOG_FILE_DAILY);
    }
}

void WeatherSensor::makeRaportNow()const
{
    string bufor = getCurrentParam();
    log.logUpdate(bufor, LOG_FILE_INSTANT);
}

inline void WeatherSensor::mailRaport()const
{
    system( "echo \"Sending an attachment of daily rapport.\" | mutt -a /home/pi/Desktop/project_1/logfile.txt -a /home/pi/Desktop/project_1/TempChart.txt -s\"Raport Sensor\" -c maciekkov@gmail.com");
}

void WeatherSensor::printSchema()
{
    for(uint32_t s = 0; s < ROW; ++s)
    {
        uint32_t num = (int)get<0>(_HourRaport[s]);
        for(uint32_t k = 0; k < COL; ++k)
        {
            if(num == k)
                tab[k][s] = 'x';
            else
                tab[k][s] = ' ';
        }
    }

    ofstream f;
    f.open("TempChart.txt");
    if(f.good())
    {
        for(uint32_t i = 0; i < ROW; ++i)
        {
            if(i >= 10)
                f << i << "|";
            else
                f << " " << i << "|";

            for(uint32_t k = 0; k < COL; ++k)
            {
                if(k%10 != 0)
                    f << " " << tab[i][k];
                else
                    f << "" << tab[i][k];
            }
            f << endl;
        }
        for(uint32_t i = 0; i < COL; ++i)
        {
            if(i/10 != 0)
                f << "|" << i;
            else
                f << "|" << i;
            if(i == 23)
                f << endl;
        }
        f.close();
    }
    else
        cout << "couldnot open file" << endl;
}

void WeatherSensor::collectData()
{
    while(!_stopThread)
    {
        auto date = BME280::readSensor();
        _secRaport.push_back(date);
        if(CountTime(_startHour, FREQUENCY_TIME_RAPORT))
        {
            _hourRaport[log.getMinuts()] = date;
            _startHour = time(NULL);
        }
        if(log.getTime() == "00:00:00")
        {
            make24HRaport();
            resetVecotrs();
        }
    }
}

bool WeatherSensor::CountTime(const time_t start, int option)
{
    time_t stop = time(NULL);
    time_t counter = stop - start;

    if(counter >= option)
        return true;
    else
        return false;
}

void WeatherSensor::resetVecotrs()
{
    _secRaport.erase(_secRaport.begin(), _secRaport.end());
    _hourRaport.erase(_hourRaport.begin(), _hourRaport.end());
}

string WeatherSensor::toString(float num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}
