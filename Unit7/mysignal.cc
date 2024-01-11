
#include <iostream>
#include <signal.h>
#include <unistd.h>

#if 0
void catchSig(int sig)
{
    // 此时的sig就是捕捉到的信号的编号
    std::cout << "进程捕捉到到了一个信号: " << sig << ", pid: " << getpid() << std::endl;
}

int main()
{
    signal(SIGINT, catchSig);
    while (true)
    {
        std::cout << "running ... pid: " << getpid() << std::endl;
        sleep(1);
    }
    return 0;
}
#endif

int main()
{
    // 这里就可以计算count能计算多少次了（可以吗？）
    alarm(1);
    int count = 0;
    while (true)
    {
        std::cout << "count: " << count++ << std::endl;
    }
    return 0;
}