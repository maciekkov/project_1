all:
	g++ BME280.cpp ControlSystem.cpp GPIO.cpp main.cpp Menu.cpp Wiersz.cpp WeatherSensor.cpp DateTime.cpp -o test -std=c++11 -pthread -lwiringPi -lwiringPiDev