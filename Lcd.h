#ifndef LCD_H
#define LCD_H
#include <wiringPi.h>
#include <lcd.h>

class Lcd
{
public:
    Lcd();
    virtual ~Lcd();
    void writeOnScreen(uint32_t col, uint32_t position, const char* text);
    void writeOnScreenWithDelay(uint32_t col, uint32_t position, const char* text, uint32_t delay);
private:
    uint32_t _lcd;
};

#endif // LCD_H

class ComponentThreadInterface {
public:
    enum EStatus {
        OK,
        BAD
    };

    virtual ~ComponentThreadInterface() {}

    virtual EStatus run() = 0;

    virtual EStatus stop() = 0;

protected:
    std::atomic<bool> _stopThread;
    std::thread _thread;
};

class Sensor : public ComponentThreadInterface {
public:

    Sensor()
    {
        _stopThread = false;
        _data = 0;
    }

    EStatus run() override {
        _thread = std::thread([this] { this->gatherData(); });

        return EStatus::OK;
    }

    EStatus stop() override {
        _stopThread = true;
        if (_thread.joinable()) _thread.join();

        return EStatus::BAD;
    }

private:

    void gatherData() {

        while (!_stopThread) {
            ++_data;
            std::cout << "Data: " << _data << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    int _data;
};

int main() {

    //auto ptr = make_unique<MenuItemTree>("Main Menu");


    Sensor s;
    s.run();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    s.stop();

    return 0;
}
