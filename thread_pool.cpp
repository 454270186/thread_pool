#include "thread_pool.hpp"

Threadpool::Threadpool(int thread_count) : pool_(std::make_shared<Pool>()) {
    assert(thread_count > 0);
    for (int i = 0; i < thread_count; i++) {
        threads_.emplace_back([pool = pool_] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(pool->mtx);
                    pool->cond.wait(lock, [pool](){ return pool->is_close || !pool->tasks.empty(); });
                    if (pool->is_close && pool->tasks.empty()) {
                        return;
                    }
                    task = std::move(pool->tasks.front());
                    pool->tasks.pop();
                }
                task();
            }
        });
    }
}

Threadpool::~Threadpool() {
    if (static_cast<bool>(pool_)) {
        {
            std::unique_lock<std::mutex> lock(pool_->mtx);
            pool_->is_close = true; // close thread pool
        }
        pool_->cond.notify_all();
        for (auto& thread : threads_) {
            thread.join();
        }
    }
}