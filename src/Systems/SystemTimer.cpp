#include "SystemTimer.h"
#include <time.h>

SystemTimer::SystemTimer()
{
    _cycleClock = clock();
}

SystemTimer::~SystemTimer()
{
    //dtor
}

void SystemTimer::ResetClock(){
    _cycleClock = clock();
}

bool SystemTimer::CanRun(int hz){
    float idealClock = (float)CLOCKS_PER_SEC / hz;

    clock_t deltaClock = clock() - _cycleClock;

    if (deltaClock >= idealClock){
        return true;
    }

    return false;
}
