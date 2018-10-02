#ifndef JOBQUEUE_H
#define JOBQUEUE_H
#include <pthread.h>
#include <list>

    typedef void (*callback_function)(void*);


    /*
A thread is not some sort of magical object that can be made to do things. It is a separate path of execution through your code.
Your code cannot be made to jump arbitrarily around its codebase unless you specifically program it to do so.
And even then, it can only be done within the rules of C++ (ie: calling functions).
You cannot kill a boost::thread because killing a thread would utterly wreck some of the most fundamental assumptions a programmer makes.
You now have to take into account the possibility that the next line doesn't execute for reasons that you can neither predict nor prevent.
This isn't like exception handling, where C++ specifically requires destructors to be called, and you have the ability to catch exceptions and do special cleanup.
You're talking about executing one piece of code, then suddenly inserting a call to some random function in the middle of already compiled code. That's not going to work.

If you want to be able to change the "task" of a thread, then you need to build that thread with "tasks" in mind.
It needs to check every so often that it hasn't been given a new task, and if it has, then it switches to doing that.
You will have to define when this switching is done, and what state the world is in when switching happens.

Todo:
    1) Spawn threads
    2) Each thread calls the Jobs, and pulls the first job from the queue
    3)

*/
/*
    class Job{
        public:
            Job();
            virtual ~Job();

            void DecrementJobs();

            void Process(callback_function f, std::list<int>entityIds){

                // Add a job for each entity id
                for (std::list<int>::iterator entityId = entityIds.begin(); entityId != entityIds.end(); ++entityId){
                   // JobQueue::Instance().QueueJob(f, *entityId, DecrementJobs)
                }

                while (remainingJobs > 0){
                    // wait for jobs to finish
                    std::this_thread::sleep_for(.01s); // possibly remove/change?
                }
            }

        private:
            int remainingJobs;


            int entityId;
    };

    class JobQueue
    {
        public:
            static JobQueue& Instance(){
                static JobQueue *instance = new JobQueue();
                return *instance;
            };

            void QueueJob(function processFunction, int processArg, function completedFunction)
            void QueueJob(callback_function f, std::list<int> entityIds);

        protected:

        private:
            JobQueue();
            virtual ~JobQueue();
            std::list<Job> _jobQueue; // queue of active jobs
            std::list<Job> _waitQueue; // queue of jobs waiting on other jobs
            int _maxThreads;
            int _activeThreads;
    };
*/
#endif // JOBQUEUE_H
