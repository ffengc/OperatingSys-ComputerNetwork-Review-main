

#ifndef __YUFC_THREAD_POOL_HPP__
#define __YUFC_THREAD_POOL_HPP__

/*
    方案2:
    queue1,queue2 两个队列
    生产队列和消费队列和指向这两个队列的指针
    我们往生产队列生产了一批任务之后，我们直接进行swap(q1,q2) (把指针做交换)
    完成交换之后，唤醒所有/一个线程
    当消费者处理完毕的时候，你也可以进行swap()
    因为我们生产和消费用的是不同的队列，未来我们要进行资源的处理的时候，仅仅只是指针
*/

#include <vector>
#include <string>
#include <queue>
#include "lockGuard.hpp"
#include "thread.hpp"
#include "Log.hpp"

#define __DEBUG_MODE__ false
const int g_thread_num = 3; // 默认三个线程

// 线程池本质就是一个生产者消费者模型
template <class T>
class thread_pool
{
private:
    std::vector<thread *> __threads;
    int __num;
    std::queue<T> __task_queue; // 任务队列
    pthread_mutex_t __lock;
    pthread_cond_t __cond;

public:
    thread_pool(int thread_num = g_thread_num)
        : __num(thread_num)
    {
        pthread_mutex_init(&__lock, nullptr);
        pthread_cond_init(&__cond, nullptr);
        for (int i = 0; i <= __num; i++)
        {
            __threads.push_back(new thread(i, routine /*线程要去干的事情*/, this /*这里可以传递this，作为thread的args*/));
        }
    }
    ~thread_pool()
    {
        for (auto &iter : __threads)
        {
            // iter->join(); // 这个线程把自已join()一下
            delete iter;
        }
        pthread_mutex_destroy(&__lock);
        pthread_cond_destroy(&__cond);
    }
    void run()
    {
        for (auto &iter : __threads)
        {
            iter->start();
            logMessage(NORMAL, "%s %s", iter->name().c_str(), "启动信息\n");
        }
    }
    void push(const T &task)
    {
        lockGuard lockguard(&__lock);
        // 向任务队列里面push任务
        __task_queue.push(task);
        pthread_cond_signal(&__cond);
    }
    static void *routine(void *args) // 线程去调用，参数一定是void* args，如果不加statics，就多了个this
    {
        // routine 本质就是消费过程
        __thread_data *td = (__thread_data *)args;
        thread_pool<T> *tp = (thread_pool<T> *)td->__args;
        // 通过这种方式，就可以让static方法调用类内的非staic属性了！
        while (true)
        {
            // 1. lock
            // 2. while看看条件变量是否符合（队列中是否有任务）如果不符合，阻塞！
            // 3. 拿到任务
            // 4. unlock
            // 5. 处理任务
            T task;
            {
                // 在这个代码块中，线程是安全的
                // 这里用个代码块，lockGuard直接就帮我们解锁了
                lockGuard lockguard(tp->get_mutex());
                while (tp->is_empty())
                    tp->wait_cond();
                // 读取任务
                task = tp->get_task(); // 任务队列是共享的
                // 解锁了
            }
            task(td->__name); // 执行任务
        }
    }

public:
    /*
        需要一批，外部成员访问内部属性的接口提供给static的routine，不然routine里面没法加锁
        下面这些接口，都是没有加锁的，因为我们认为，这些函数被调用的时候，都是在安全的上下文中被调用的
        因为这些函数调用之前，已经加锁了，调用完，lockGuard自动解锁
    */
    pthread_mutex_t *get_mutex() { return &__lock; }
    void wait_cond() { pthread_cond_wait(&__cond, &__lock); }
    bool is_empty() { return __task_queue.empty(); }
    T get_task()
    {
        T t = __task_queue.front();
        __task_queue.pop();
        return t; // 拷贝返回
    }
};
#endif