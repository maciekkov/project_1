all:
	g++ Menu.cpp BME280.cpp ControlSystem.cpp GPIO.cpp main.cpp  Wiersz.cpp WeatherSensor.cpp DateTime.cpp Lcd.cpp BusyWaitThreadInterface.cpp  -o test -std=c++11 -pthread -lwiringPi -lwiringPiDev
