
#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>

// 临界资源问题
// 如果多个线程同时访问同一个全局变量，并对他进行数据计算，会出问题吗
// 抢票
int tickets = 10000;
void *getTickets(void *args)
{
    (void)args;
    while (true)
    {
        if (tickets > 0)
        {
            usleep(1000);
            printf("%p: %d\n", pthread_self(), tickets);
            tickets--;
        }
        else
            break; // 没有票了
    }
    return nullptr;
}
int main()
{
    pthread_t t1, t2, t3;
    // 多线程抢票的逻辑
    pthread_create(&t1, nullptr, getTickets, nullptr);
    pthread_create(&t2, nullptr, getTickets, nullptr);
    pthread_create(&t3, nullptr, getTickets, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    return 0;
}