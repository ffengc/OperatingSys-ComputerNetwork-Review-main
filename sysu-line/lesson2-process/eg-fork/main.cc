

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

void test1()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        /* fork error */
        std::cerr << "Fork failed" << std::endl;
        exit(1);
    }
    else if (pid == 0)
    {
        /* child process */
        execlp("/bin/ls", "ls", nullptr);
    }
    else
    {
        /* father process */
        wait(nullptr);
        std::cout << "wait shild success" << std::endl;
    }
}

int main()
{
    test1();
    return 0;
}