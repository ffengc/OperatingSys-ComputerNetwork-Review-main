
#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>

#if 0
/* 初识线程 */
void *threadRun(void *args)
{
    const std::string name = (char *)args;
    while(true)
    {
        std::cout << name << ", pid: " << getpid() << std::endl;
        // 线程在进程内部运行，所以getpid()的结果应该是对应父进程的pid
        sleep(1);
    }
}
int main()
{
    pthread_t tid[5];
    char name[64];
    for (int i = 0; i < 5; i++)
    {
        snprintf(name, sizeof(name), "%s-%d", "thread", i); // 线程的编号
        pthread_create(tid + i, nullptr, threadRun, (void *)name);
        sleep(1);
    }
    while (true)
    {
        std::cout << "main thread, pid: " << getpid() << std::endl;
        sleep(3);
    }
    return 0;
}
#endif

#if 0
/* 线程等待 */
void *threadRoutine(void *args)
{
    // 要传递给线程的东西，可以用void* 的形式在pthread_create的第四个参数里面传递过来
    int i = 0;
    while (true)
    {
        std::cout << "new thread: " << (char *)args << " running ..." << std::endl;
        sleep(1);
        // if (i++ == 5)
        //     break; //
        // pthread_exit((void *)13);
    }
    // 如果我想给主线程返回一个东西呢，要用void*的形式返回
    return (void *)10;
}
int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadRoutine, (void *)"thread 1");
    void *ret = nullptr;     // 线程给我返回的结果
    pthread_cancel(tid);     // cancel 这个线程
    pthread_join(tid, &ret); // 默认会阻塞等待
    std::cout << "main thread wait done, main quit." << std::endl;
    printf("%d\n", ret);
    return 0;
}
#endif

/* 全局变量被所有线程共享 */
#if 0
int g_val = 0;
void *threadRoutine(void *args)
{
    while (1)
    {
        std::cout << (char *)args << ", "
                  << " &g_val: " << &g_val << ", g_val: " << g_val << std::endl;
        g_val++;
        sleep(1);
    }
}
int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadRoutine, (void *)"thread_1");
    printf("%lu, %p\n", tid, tid);
    while (true)
    {
        std::cout << "main thread: "
                  << " &g_val: " << &g_val << ", g_val: " << g_val << std::endl;
        // 我们发现新线程对g_val的改动，主线程可以看到
        sleep(1);
    }
    return 0;
}
#endif