

#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <assert.h>

/*
    这里是非阻塞等待线程的一个小demo应用
*/

typedef void (*handler_t)();     // 函数指针类型
std::vector<handler_t> handlers; // 这个数组里面存放函数指针

void fun_one() { std::cout << "task 1 doing ... " << std::endl; }
void fun_two() { std::cout << "task 2 doing ... " << std::endl; }

// 设置对应的回调
void Load()
{
    // 注册
    handlers.push_back(fun_one);
    handlers.push_back(fun_two);
}

int main()
{
    pid_t id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        // 子进程
        int cnt = 5;
        while (cnt--)
        {
            printf("我是子进程, 我的pid: %d, cnt: %d\n", getpid(), cnt);
            sleep(1);
        }
        exit(11); // 仅仅用来测试，如果正常来说是要返回0的。
    }
    else
    {
        int quit = 0;
        while (!quit)
        {
            int status = 0;
            pid_t res = waitpid(-1, &status, WNOHANG); // 非阻塞等待
            if (res > 0)
            {
                // 等待成功，子进程退出了
                printf("等待子进程成功, 退出码: %d\n", WEXITSTATUS(status));
                quit = 1;
            }
            else if (res == 0)
            {
                // 等待成功，但是子进程没有退出！
                printf("子进程还在执行当中，父进程可以等一等，处理一下其他事情\n");
                if (handlers.empty())
                {
                    Load();
                }
                for(auto it : handlers)
                {
                    it(); // 执行已经注册好的事情
                }
            }
            else
            {
                // 等待失败，其实就是waitpid等待失败，比如我们id写错了，没有id这个进程，一般才会出现这个问题
                printf("waitpid失败\n");
                quit = 1;
            }
            sleep(1);
        }
    }
    return 0;
}