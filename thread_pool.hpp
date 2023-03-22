#ifndef _THREAD_POOL
#define _THREAD_POOL
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <cassert>

class Threadpool {
public:
    // thread_count is max number of work thread
    explicit Threadpool(int thread_count = 10);
    Threadpool() = default;
    Threadpool(Threadpool&&) = default;
    ~Threadpool();

    template <class F>
    void add_task(F&& task);

private:
    struct Pool {
        std::mutex mtx;
        std::condition_variable cond;
        bool is_close;
        std::queue<std::function<void()>> tasks; // work queue
    };
    std::shared_ptr<Pool> pool_;
};

#endif // _THREAD_POOL