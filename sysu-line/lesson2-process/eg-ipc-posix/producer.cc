
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <string>

const int SIZE = 4096;   // 共享内存的大小
const char *NAME = "OS"; // 共享内存的名字

void make_producer()
{
    int shm_fd = 0;      // 共享内存文件描述符
    void *ptr = nullptr; // 指向共享内存的指针
    // 创建共享内存对象
    shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    // 配置这个共享内存的信息
    ftruncate(shm_fd, SIZE);
    // 把共享内存映射到ptr上
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // 向共享内存写数据
    while (1)
    {
        std::string mesg;
        std::cout << "[please input the mesg]# ";
        std::cin >> mesg;
        if (mesg == "quit")
            break;
        sprintf((char *)ptr, "%s", mesg.c_str());
        ptr += mesg.size();
    }
    // 最后需要移除shm对象，我认为应该是producer来做这件事的，而不是consumer
    shm_unlink(NAME);
}

int main()
{
    make_producer();
    return 0;
}