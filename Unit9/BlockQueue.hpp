

#ifndef __YUFC_BLOCKQUEUE__
#define __YUFC_BLOCKQUEUE__

#include <iostream>
#include <queue>
#include <pthread.h>
#include "lockGuard.hpp"

// std::queue 不是线程安全的 -- 不是的

const int gDefaultCap = 5;
template <class T>
class BlockQueue
{
private:
    std::queue<T> __bq;
    size_t __capacity;      // 队列的容量上限
    pthread_mutex_t __mtx;  // 通过互斥锁保证队列安全
    pthread_cond_t __empty; // 用它来表示bq是否空的条件
    pthread_cond_t __full;  // 用它来表示bq是否满的条件
private:
    bool __isQueueEmpty() { return __bq.size() == 0; }
    bool __isQueueFull() { return __bq.size() == this->__capacity; }

public:
    BlockQueue(size_t capacity = gDefaultCap)
        : __capacity(capacity)
    {
        pthread_mutex_init(&__mtx, nullptr);
        pthread_cond_init(&__empty, nullptr);
        pthread_cond_init(&__full, nullptr);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&__mtx);
        pthread_cond_destroy(&__empty);
        pthread_cond_destroy(&__full);
    }

public:
    // 生产者push
    void push(const T &in)
    {
        /*
            1. 先检测当前的临界资源是否能够访问条件
            注意!
            此时真的没有问题吗？
            pthread_cond_wait(): 我们现在是在临界区中的！我们持有锁！如果我去等待了，锁怎么办？！
            pthread_cond_wait第二个参数是一把锁，意义在于：
            当成功调用wait之后，传入的锁会被自动释放！
            这就是pthread_cond_wait第二个参数的意义！
            如果我被唤醒时：我从哪里醒来呢？？从哪里阻塞挂起，就从哪里唤醒（我们先保留，等等再解释）
            我们醒来的时候，是在临界资源中唤醒的！
            此时，pthread_cond_wait, 会自动帮助我们先层获取锁(这些动作都是原子的，不用我们操心)
            但是，谁来唤醒呢？生产者的唤醒是由消费者做的！消费者给bq腾出位置，生产者就能生产了！
        */
        lockGuard lockguard(&__mtx);
        while (__isQueueFull())
        {
            pthread_cond_wait(&__full, &__mtx);
        }
        __bq.push(in);
        if (__bq.size() >= __capacity / 2)
            pthread_cond_signal(&__empty); // 如果如果队列中的元素个数超过一半了，提醒消费者取
    }
    void pop(T *out)
    {
        lockGuard lockguard(&__mtx);
        while (__isQueueEmpty())
        {
            pthread_cond_wait(&__empty, &__mtx);
        }
        *out = __bq.front();
        __bq.pop();
        pthread_cond_signal(&__full); // 一旦取走一个，生产者就能继续push
    }
};

#endif
