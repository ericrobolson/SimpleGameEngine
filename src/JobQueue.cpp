#include "JobQueue.h"
#include <pthread.h>

JobQueue::JobQueue()
{
    _maxThreads = 10;
    _activeThreads = 0;
}

JobQueue::~JobQueue()
{
    //dtor
}
