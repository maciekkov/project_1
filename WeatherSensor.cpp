#include <fstream>
#include "WeatherSensor.h"

using namespace std;

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

int WeatherSensor::runThreadCollectData() 
{
   _thread = thread(&WeatherSensor::collectData, this);
   return 1;
}

int WeatherSensor::stopThreadCollectData() 
{
    BusyWaitThreadInterface::_stopThread = true;
    if(_thread.joinable())
		_thread.join();
    return 1;
}

string WeatherSensor::getAvg(const vector<tuple<double, int, int> >& data, int num)
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

string WeatherSensor::getDataForEachHour(int i)
{
    double	  tsuma = get<0>(_hourRaport[i]);
    double	  hsuma = get<1>(_hourRaport[i]);
    double	  psuma = get<2>(_hourRaport[i]);

    string buffor = "Temp:" + toString(tsuma)+"     Hum:" + toString(hsuma) + " Press:" + toString(psuma);
    return buffor;
}

string WeatherSensor::getCurrentParam()
{
    double	  tsuma = get<0>(_secRaport.back());
    double	  hsuma = get<1>(_secRaport.back());
    double	  psuma = get<2>(_secRaport.back());

    string buffor = "Temp: " + toString(tsuma) + "     Hum:" + toString(hsuma) + " Press:" + toString(psuma);
    return buffor;
}

void WeatherSensor::make24HRaport()
{
    string bufor;
    for(uint i = 0; i <_hourRaport.size(); ++i)
    {
        bufor = getDataForEachHour(i);
        log.logUpdate(bufor, LOG_FILE_DAILY);
    }
}

void WeatherSensor::makeRaportNow()
{
    string bufor = getCurrentParam();
    log.logUpdate(bufor, LOG_FILE_INSTANT);
}

void WeatherSensor::mailRaport()
{
    system( "echo \"Sending an attachment of daily rapport.\" | mutt -a /home/pi/Desktop/project_1/logfile.txt -a /home/pi/Desktop/project_1/TempChart.txt -s\"Raport Sensor\" -c maciekkov@gmail.com");
}

bool WeatherSensor::getThreadFlag()
{
	return _stopThread;
}

void WeatherSensor::printSchema()
{
    for(uint32_t s = 0; s < ROW; ++s)
    {
        uint32_t num = (int)get<0>(_hourRaport[s]);
        for(uint32_t k = 0; k < COL; ++k)
        {
            if(num == k)
                _tab[k][s] = 'x';
            else
                _tab[k][s] = ' ';
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
                    f << " " << _tab[i][k];
                else
                    f << "" << _tab[i][k];
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
        if(countTime(_startHour, FREQUENCY_TIME_RAPORT))
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

bool WeatherSensor::countTime(const time_t start, int option)
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

string WeatherSensor::toString(float num)const
{
    stringstream ss;
    ss << num;
    return ss.str();
}
