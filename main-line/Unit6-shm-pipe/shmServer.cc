

#include "comm.hpp"

Init init;
/*
    这里会自动调用Init的构造，创建一个管道文件
*/

// 为了让key更好看，和命令行输出的对应起来
// 写一个转换成16进制的函数
std::string TransToHex(key_t k)
{
    char buffer[32];
    snprintf(buffer, sizeof buffer, "0x%x", k);
    return buffer;
}

void start_server()
{
    // 1. 创建公共的key值
    key_t k = ftok(PATH_NAME, PROJ_ID);
    assert(k != -1);
    Log("create key done", Debug) << " server key: " << TransToHex(k) << std::endl;
    // 2. 创建共享内存
    int shmid = shmget(k, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    assert(shmid != -1); // 保证shmget调用成功
    Log("create shm done", Debug) << " shmid: " << shmid << std::endl;
    // 3. 将制定的共享内存，挂接到自己的地址空间
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    Log("attach shm done", Debug) << " shmid: " << shmid << std::endl;

    // 4. 开始通信
    int fd = openFIFO(FIFO_NAME, READ);
    for (;;)
    {
        WaitFIFO(fd); // 作为Server，先等等！先等别人叫醒你，你才进行读取，别一直读
        printf("%s\n", shmaddr);
        if (strcmp(shmaddr, "quit") == 0)
            break;
    }

    // 5. 解除挂接
    int n = shmdt(shmaddr);
    assert(n != -1);
    (void)n;
    Log("detach shm done", Debug) << " shmid: " << shmid << std::endl;
    // 6. 删除共享内存
    n = shmctl(shmid, IPC_RMID, nullptr);
    assert(n != -1);
    (void)n;
    Log("delete shm done", Debug) << " shmid: " << shmid << std::endl;
    CloseFIFO(fd);
}

int main()
{
    start_server();
    return 0;
}