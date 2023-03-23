#include <iostream>
#include <cstdio>
#include <chrono>
#include <memory>
#include <future>
#include "thread_pool.hpp"

int main() {
    Threadpool pool(50);
    
    for (int i = 0; i < 1000; i++) {
        pool.add_task([i]() {
            // std::cout << "Task " << i << " started...\n" << std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            // std::cout << "Task " << i << " finished!" << std::endl;
            printf("Task %d start...\n", i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            printf("Task %d finished\n", i);
        });
    }

    //std::this_thread::sleep_for(std::chrono::seconds(10)); // 等待所有任务执行完毕
    return 0;
}