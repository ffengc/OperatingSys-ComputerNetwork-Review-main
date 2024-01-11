

/*
    用这个程序一直跑一个循环
    gcc loop.c -o loop.out
*/

#include <unistd.h>
#include <stdio.h>

int main()
{
    int cnt = 0;
    printf("loop.out start running\n");
    while (1)
    {
        cnt++;
        printf("\tloop.out is running ... pid: %d, count: %d\r", getpid(), cnt);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}