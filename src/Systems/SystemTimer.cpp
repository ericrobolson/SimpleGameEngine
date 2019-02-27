#include "SystemTimer.h"
#include <time.h>

SystemTimer::SystemTimer()
{
    _cycleClock = clock();

    _clocksPerSecond.SetValueFromDouble((long double)CLOCKS_PER_SEC);

}

SystemTimer::~SystemTimer()
{
    //dtor
}

void SystemTimer::ResetClock(){
    _cycleClock = clock();
}

bool SystemTimer::CanRun(FixedPointInt hz){
    FixedPointInt idealClock = _clocksPerSecond / hz;

    clock_t deltaClock = clock() - _cycleClock;

    if (deltaClock >= (int)idealClock){
        return true;
    }

    return false;
}
