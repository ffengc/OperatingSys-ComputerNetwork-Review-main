
#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    进程替换相关代码
*/

#if false
int main()
{
    std::cout << "begin to run the main function" << std::endl;
    execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
    std::cout << "finish to run the main function" << std::endl;
    return 0;
}
#endif



#if false
// 程序替换
int main()
{
    pid_t id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        // 子进程
        std::cout << "子进程开始运行 ... " << std::endl;
        // execl("/usr/bin/ls", "ls", "-al", NULL);
        char* const argv[] = {"ls", "-al", NULL};
        execv("/usr/bin/ls", argv);
        exit(1); // 如果调用失败，直接退出
    }
    else
    {
        // 父进程
        std::cout << "父进程开始运行, pid: " << getpid() << std::endl;
        int status = 0;
        pid_t id = waitpid(-1, &status, 0); // 阻塞等待
        if (id > 0)
        {
            std::cout << "wait success, exit code: " << WEXITSTATUS(status) << std::endl;
        }
    }
    return 0;
}
#endif


// 用一个C++去调用一个python
int main()
{
    pid_t id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        // 子进程
        std::cout << "child proc working ..." << std::endl;
        execl("/usr/bin/python", "python", "hello_python.py", NULL);
        std::cout << "called python failed!" << std::endl;
        exit(1);
    }
    else
    {
        // 父进程
        std::cout << "father proc working, pid: " << getpid() << std::endl;
        int status = 0;
        pid_t id = waitpid(-1, &status, 0); // 阻塞等待
        if (id > 0)
        {
            std::cout << "wait success, exit code: " << WEXITSTATUS(status) << std::endl;
        }
    }
    return 0;
}