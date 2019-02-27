#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H
#include <time.h>

#include "FixedPointInt.h"
using namespace SGE_Math;

class SystemTimer
{
    public:
        SystemTimer();
        virtual ~SystemTimer();
        bool CanRun(FixedPointInt hz);
        void ResetClock();

    private:
        clock_t _cycleClock;
        FixedPointInt _clocksPerSecond;
};

#endif // SYSTEMTIMER_H
