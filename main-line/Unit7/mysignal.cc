

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <assert.h>

#if 0
void handler(int signum)
{
    std::cout << "捕获了一个信号: " << signum << std::endl;
}
int main()
{
    // 内核数据类型，但是我们下面这些定义是在user栈上定义的
    struct sigaction act, oact;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = handler;
    // 把上面定义的东西丢到进程的pcb里面去
    sigaction(2, &act, &oact);
    std::cout << "default action: " << oact.sa_handler << std::endl;
    while (true)
        sleep(1);
    return 0;
}
#endif

int flag = 0;
void changeFlag(int signum)
{
    (void)signum;
    std::cout << "change flag: " << flag;
    flag = 1;
    std::cout << "->" << flag << std::endl;
}
int main()
{
    signal(2, changeFlag); // 收到二号信号去改一下全局的flag
    while (!flag)          // 如果flag还是0
    {
        sleep(1);
    }
    std::cout << "进程正常退出后: " << flag << std::endl;
    return 0;
}