#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <tuple>

// Based on https://github.com/progschj/ThreadPool

class JobQueue {
public:
    const static int MaxBatches = 214748364;

    static JobQueue& Instance(){
            int threads = std::thread::hardware_concurrency() -1; // ensure we don't use more threads than needed

            if (threads <= 0){
                threads = 1;
            }

            static JobQueue *instance = new JobQueue(threads);
            return *instance;
        };

    int GetNextBatchId(){
        // Boundary handling to prevent int overflow
        if (_batchId >= MaxBatches){
            _batchId = 0;
        }

        // Ensure we don't overwrite an existing batch
        std::unique_lock<std::mutex> lock(this->_jobMapMutex);

        while (_jobMap[_batchId] > 0){
            _batchId++;
        }

        // Return the batchId
        int batchId = _batchId;
        _batchId++;

        return batchId;
    }

    bool DoJobsRemain(int batchId){
        std::unique_lock<std::mutex> lock(this->_jobMapMutex);

        if (batchId > MaxBatches || batchId < 0){
            return false;
        }

        return _jobMap[batchId] > 0;
    }


    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

    template<class F, class... Args>
    auto enqueue(int batchId, F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

    ~JobQueue();
private:
    JobQueue(size_t);

    int _batchId = 0;

    int _jobMap[MaxBatches] = {0}; // The list of jobs remaining for each batch id

    std::mutex _jobMapMutex;

    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks; // Todo: change to a tuple with the batchId and the function

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline JobQueue::JobQueue(size_t threads)
    :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(
            [this]
            {
                for(;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto JobQueue::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    return enqueue(GetNextBatchId(), f, args...);
}

template<class F, class... Args>
auto JobQueue::enqueue(int batchId, F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    // Ensure a valid batchid is used
    if (batchId > MaxBatches || batchId < 0){
        batchId = GetNextBatchId();
    }

    // Add the job to the job map
    std::unique_lock<std::mutex> lock(_jobMapMutex);
    _jobMap[batchId]++;

    // enqueue and construct future
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline JobQueue::~JobQueue()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}

#endif // JOBQUEUE_H
