
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const int SIZE = 4096;   // 共享内存的大小
const char *NAME = "OS"; // 共享内存的名字

void make_consumer()
{
    int shm_fd = 0;
    void *ptr = nullptr;
    shm_fd = shm_open(NAME, O_RDONLY, 0666);
    while (1)
    {
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        std::cout << (char *)ptr << std::endl;
        sleep(1); // 读慢一点
    }
}
int main()
{
    make_consumer();
    return 0;
}