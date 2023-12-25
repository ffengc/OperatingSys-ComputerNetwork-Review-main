
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/*
    这里都是进程等待的代码
*/

#if false
int main()
{
    std::cout << "hello world" << std::endl;
    char* p = nullptr;
    *p = 1;
    return 0;
}
#endif

#if false
int main()
{
    std::cout << "hello world";
    sleep(3);
    _exit(1);
    return 0;
}
#endif

// wait / waitpid
#if false
int main()
{
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (id == 0)
    {
        // 子进程
        int cnt = 5;
        while (cnt)
        {
            printf("cnt: %d, 我是子进程, pid: %d, ppid: %d\n", cnt, getpid(), getppid());
            sleep(1);
            cnt--;
        }
        exit(0); // 子进程结束
    }
    else
    {
// 父进程
#if false
        while(1)
        {
            printf("我是父进程, pid: %d, ppid: %d\n", getpid(), getppid());
            sleep(1);
        }
#endif
        printf("我是父进程, pid: %d, ppid: %d\n", getpid(), getppid());
        pid_t ret = wait(NULL); // 注意，这里是阻塞式等待
        if(ret > 0)
        {
            printf("父进程等待子进程成功，子进程的pid: %d\n", ret);
        }
    }
    return 0;
}
#endif


// waitpid
#if false
int main()
{
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (id == 0)
    {
        // 子进程
        int cnt = 5;
        while (cnt)
        {
            printf("cnt: %d, 我是子进程, pid: %d, ppid: %d\n", cnt, getpid(), getppid());
            sleep(1);
            char *p = nullptr;
            *p = 1; // 构造一个段错误
            cnt--;
        }
        exit(105); // 子进程结束
    }
    else
    {
        // 父进程
        printf("我是父进程, pid: %d, ppid: %d\n", getpid(), getppid());
        int status = 0;                      // 输出参数
        pid_t ret = waitpid(id, &status, 0); // 注意，这里是阻塞式等待
#if false
        if (ret > 0)
        {
            printf("父进程等待子进程成功，子进程的pid: %d, status: %d, 信号: %d, 退出码: %d\n", ret, status, (status & 0x7F), (status >> 8) & (0xFF));
        }
#endif
        if (WIFEXITED(status))
        {
            printf("子进程执行完毕，子进程的退出码: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("子进程异常退出: %d\n", WIFEXITED(status));
        }
    }
    return 0;
}
#endif