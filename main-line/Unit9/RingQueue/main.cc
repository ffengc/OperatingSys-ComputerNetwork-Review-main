

#include <time.h>
#include <stdlib.h>
#include "ringQueue.hpp"
#include <sys/types.h>
#include <unistd.h>

void *consumer(void *args)
{
    ring_queue<int> *rq = (ring_queue<int> *)args;
    while (true)
    {
        int x = 0;
        rq->pop(&x);
        std::cout << pthread_self() << " consumer: " << x << std::endl;
        sleep(1);
    }
}

void *productor(void *args)
{
    ring_queue<int> *rq = (ring_queue<int> *)args;
    while (true)
    {
        // 1. 构建数据或任务对象 -- 一般是可以从外部来 -- 不要忽略它的时间消耗问题
        int x = rand() % 100 + 1;
        // 2. 推送到环形队列中
        rq->push(x); // 完成生产的过程
        std::cout << pthread_self() << " productor: " << x << std::endl;
    }
}

int main()
{
    srand((uint64_t)time(nullptr) ^ getpid() ^ 123124);
    ring_queue<int> *rq = new ring_queue<int>();
    // rq->debug();
    pthread_t c[3], p[2]; // 两个生产者，三个消费者
    pthread_create(c, nullptr, consumer, (void *)rq);
    pthread_create(c + 1, nullptr, consumer, (void *)rq);
    pthread_create(c + 2, nullptr, consumer, (void *)rq);

    pthread_create(p, nullptr, productor, (void *)rq);
    pthread_create(p + 1, nullptr, productor, (void *)rq);

    pthread_join(*c, nullptr);
    pthread_join(*(c + 1), nullptr);
    pthread_join(*p, nullptr);
    pthread_join(*(p + 1), nullptr);

    return 0;
}