#include <stdio.h>
#include <iostream>
#include "ControlSystem.h"

using namespace std;

int main()
{
	wiringPiSetup();
    ControlSystem control;
    control.run();

    return 0;
}
