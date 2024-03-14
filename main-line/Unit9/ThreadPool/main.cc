

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "threadPool.hpp"
#include "Task.hpp"
#include "Log.hpp"

int main()
{
    srand((uint64_t)time(nullptr) ^ getpid() ^ 1231);
    thread_pool<Task> *tp = new thread_pool<Task>();
    tp->run();
    while (true)
    {
        // 生产的过程
        // 制作任务的时候是要花时间的
        int x = rand() % 100 + 1;
        usleep(1231);
        int y = rand() % 30 + 1;
        Task t(x, y, [](int x, int y) -> int
               { return x + y; });
        logMessage(NORMAL, "任务制作完成: %d + %d = ? \n", x, y);
        // 推送任务到线程池中
        tp->push(t);
        sleep(1);
    }
    return 0;
}