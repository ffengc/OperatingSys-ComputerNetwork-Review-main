

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#define READ_END 0
#define WRITE_END 1

void report_and_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

int main()
{
    int pipe_fd[2]; // 这些我都很熟了
    std::string str = "Nature's first green is gold\n";
    if (pipe(pipe_fd) < 0)
        report_and_exit("call pipe fail");
    pid_t pid = fork();
    if (pid < 0)
        report_and_exit("fork fail");
    if (pid == 0)
    {
        // 子进程
        close(pipe_fd[WRITE_END]); // 关闭写端，子进程只读
        char buffer[1024];
        while (int sz = read(pipe_fd[READ_END], &buffer, 1) > 0)
        {
            buffer[sz] = 0; // 添加一个\0
            std::cout << buffer;
        }
        // 如果while break掉了，说明写端已经关闭了
        close(pipe_fd[READ_END]);
        exit(0); // 课件的 _exit(0) 是系统调用，具体细节我也很熟悉了
    }
    // 父进程
    close(pipe_fd[READ_END]);                           // 父进程只写
    write(pipe_fd[WRITE_END], str.c_str(), str.size()); // 只写了一句话
    close(pipe_fd[WRITE_END]);
    wait(nullptr); // 回收子进程
    return 0;
}