

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

void MakePipeCommunication()
{
    // 1. 创建管道
    int pipefd[2] = {0}; // pipefd[0]: 读端, pipefd[1]: 写端
    int n = pipe(pipefd);
    assert(n != -1); // 编译模式debug模式下assert才是有效的，release的时候是无效的
    (void)n;         // 表明n被使用过
#if DEBUG
    // 看看pipefd[]里面存的文件描述符都是些啥东西
    std::cout << "pipefd[0]: " << pipefd[0] << std::endl; // 3
    std::cout << "pipefd[1]: " << pipefd[1] << std::endl; // 4
#endif
    // 2. 创建子进程
    pid_t id = fork();
    assert(id != -1);
    if (id == 0)
    {
        // 子进程
        // 3. 构建单向通信的管道 -- 父进程写入，子进程读取
        // 3.1 关闭子进程不需要的fd
        close(pipefd[1]); // 把写端关闭
        // 通信
        char buffer[1024];
        // 写入的一端：如果fd没有关闭，读端如果有数据就读，如果没有数据，就等（阻塞）
        // 写入的一端：如果fd关闭了，读取的一端read会返回0，表示读到了文件的结尾！
        while (true)
        {
            ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1);
            if (s > 0)
            {
                // 读取成功
                buffer[s] = 0;
                std::cout << "child get a mesg, pid: [" << getpid() << "] Father's mesg: " << buffer << std::endl;
            }
            else if (s == 0)
            {
                // read返回时0，说明写端fd关闭了
                std::cout << "writer(father) quit, I(child) quit too!" << std::endl;
                break;
            }
        }
        exit(0); // 子进程关闭
    }
    // 这里是父进程
    close(pipefd[0]); // 关闭读取端
    // 写入
    std::string mesg = "我是父进程，我正在给你发消息";
    int count = 0; // 记录父进程发送信息的条目数量
    char send_buffer[1024];
    while (true)
    {
        // 3.2 构建一个变化的字符串
        snprintf(send_buffer, sizeof(send_buffer), "%s[%d] : %d", mesg.c_str(), getpid(), count);
        // 3.3 发送
        write(pipefd[1], send_buffer, strlen(send_buffer)); // 不需要+1
        count++;
        // 3.4 故意sleep一下
        sleep(1);
        if (count == 10)
        {
            std::cout << "writer(father/me) quit" << std::endl;
            break;
        }
    }
    close(pipefd[1]); // 推出之后关闭文件描述符
    pid_t ret = waitpid(id, nullptr, 0);
    assert(ret > 0);
    (void)ret;
}

int main()
{
    MakePipeCommunication();
    return 0;
}