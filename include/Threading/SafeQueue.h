#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <mutex>
#include <queue>

template <typename T>
class SafeQueue
{
    public:
        SafeQueue() {}
        virtual ~SafeQueue() {}

        bool empty(){
            std::unique_lock<std::mutex> lock(_mutex);
                return _queue.empty();
        }

        int size(){
            std::unique_lock<std::mutex> lock(_mutex);
                return _queue.size();
        }

        void enqueue(T& t){
            std::unique_lock<std::mutex> lock(_mutex);
                _queue.push(t);
        }

        bool dequeue(T& t){
            std::unique_lock<std::mutex> lock(_mutex);
                if (_queue.empty()){
                    return false;
                }

                t = std::move(_queue.front());
                _queue.pop();

                return true;
        }

    private:
        std::queue<T> _queue;
        std::mutex _mutex;
};

#endif // SAFEQUEUE_H
