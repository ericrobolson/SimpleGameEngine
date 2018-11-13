#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H
#include <time.h>


class SystemTimer
{
    public:
        SystemTimer();
        virtual ~SystemTimer();
        bool CanRun(int hz);
        void ResetClock();

    private:
        clock_t _cycleClock;
};

#endif // SYSTEMTIMER_H
