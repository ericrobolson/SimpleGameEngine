#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "SafeQueue.h"

class ThreadPool {
    private:
        class ThreadWorker {
            private:
                int _id;
                ThreadPool * _threadPool;
            public:
                ThreadWorker(ThreadPool * pool, const int id) : _threadPool(pool), _id(id) {}

                void operator()() {
                    std::function<void()> func;
                    bool dequeued;
                    //while (!_threadPool->_shutdown) {
                    while(true){
                        {
                        std::unique_lock<std::mutex> lock(_threadPool->_mutex);
                        if (_threadPool->_queue.empty()) {
                        _threadPool->_conditionalLock.wait(lock);
                        }
                        dequeued = _threadPool->_queue.dequeue(func);
                        if (_threadPool->_shutdown){
                            break;
                        }
                        }

                    if (dequeued) {
                        func();
                    }
                    }
                }
            };

        bool _shutdown;
        SafeQueue<std::function<void()>> _queue;
        std::vector<std::thread> _threads;
        std::mutex _mutex;
        std::condition_variable _conditionalLock;

        ///Ctor
        ThreadPool(const int numThreads) : _threads(std::vector<std::thread>(numThreads)), _shutdown(false) {
            for (int i = 0; i < _threads.size(); ++i) {
                _threads[i] = std::thread(ThreadWorker(this, i));
            }
        }

        ///Dtor
        ~ThreadPool(){
             _shutdown = true;
            _conditionalLock.notify_all();

            for (int i = 0; i < _threads.size(); ++i) {
                if(_threads[i].joinable()) {
                    _threads[i].join();
                }
            }
        }

    public:
        static ThreadPool& Instance(){
            int threads = std::thread::hardware_concurrency() -1; // ensure we don't use more threads than needed

            if (threads <= 0){
             //   threads = 1;
            }

           // threads = 1; // todo: right now there's some sort of issue when threads > 1

            static ThreadPool *instance = new ThreadPool(threads);
            return *instance;
        };

        bool IsEmpty(){
            return _queue.empty();
        }

        // Submit a function to be executed asynchronously by the pool
        template<typename F, typename...Args>
        auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
            // Create a function with bounded parameters ready to execute
            std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            // Encapsulate it into a shared ptr in order to be able to copy construct / assign
            auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

            // Wrap packaged task into void function
            std::function<void()> wrapper_func = [task_ptr]() {
                (*task_ptr)();
            };

            // Enqueue generic wrapper function
            _queue.enqueue(wrapper_func);

            // Wake up one thread if its waiting
            _conditionalLock.notify_one();

            // Return future from promise
            return task_ptr->get_future();
        }
};

#endif // THREADPOOL_H
