

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 2
#define ITERATIONS 10000

#define __if_add_lock false

int global_int = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
#if __if_add_lock
        pthread_mutex_lock(&mutex); // 要加锁
        global_int++;
        pthread_mutex_unlock(&mutex);
#else
        global_int++;
#endif
    }
    return nullptr;
}
void *decrement(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
#if __if_add_lock
        pthread_mutex_lock(&mutex); // 要加锁
        global_int--;
        pthread_mutex_unlock(&mutex);
#else
        global_int--;
#endif
    }
    return nullptr;
}
int main()
{
#if __if_add_lock
    printf("------------- with locks -------------\n");
#else
    printf("------------- without locks -------------\n");
#endif
    pthread_t threads[NUM_THREADS];
    clock_t start_time, end_time;
    // 记录线程创建开始的时间
    start_time = clock();
    // 创建并运行两个线程
    pthread_create(&threads[0], nullptr, increment, nullptr);
    pthread_create(&threads[1], nullptr, decrement, nullptr);
    // 等待线程结束
    pthread_join(threads[0], nullptr);
    pthread_join(threads[1], nullptr);
    // 记录线程结束的时间
    end_time = clock();
    double total_time = (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC;
    // 打印线程任务总共花费的时间
    printf("Total time taken by threads: %lf milliseconds\n", total_time);
    // 打印全局整数的值
    printf("Global integer value: %d\n", global_int);
    return 0;
}