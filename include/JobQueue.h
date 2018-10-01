#ifndef JOBQUEUE_H
#define JOBQUEUE_H
#include <pthread.h>
#include <list>

class JobQueue
{
    public:
        JobQueue();
        virtual ~JobQueue();
        void AddJob();

    protected:

    private:
        std::list<int> _jobQueue; // queue of active jobs
        std::list<int> _waitQueue; // queue of jobs waiting on other jobs
        int _maxThreads;
        int _activeThreads;
};

#endif // JOBQUEUE_H
