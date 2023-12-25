
#include "comm.hpp"

// 为了让key更好看，和命令行输出的对应起来
// 写一个转换成16进制的函数
std::string TransToHex(key_t k)
{
    char buffer[32];
    snprintf(buffer, sizeof buffer, "0x%x", k);
    return buffer;
}

int main()
{
    // 这里可以生成一个唯一的k，在client里面也这样搞，也能得到这个k
    key_t k = ftok(PATH_NAME, PROJ_ID);
    assert(k != -1);
    Log("create key done!", Debug) << "client key: " << k << std::endl;
    int shmid = shmget(k, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1)
    {
        // 创建共享内存失败
        perror("shmget");
        exit(1);
    }
    Log("creat shm done!", Debug) << "shmid: " << shmid << std::endl;
    // 将制定的共享内存，attach到自己的地址空间上去
    // sleep(5);
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    // sleep(5); // 我们会看到挂接数从0变成1

    // 通信
    // ...
    // 将共享内存当做一个大的字符串
    for (;;)
    {
        printf("%s\n", shmaddr);
        if (strcmp(shmaddr, "quit") == 0)
            break; // 输入quit的时候直接退出通信
        sleep(1);
    }

    // dettach
    int n = shmdt(shmaddr);
    assert(n != -1);
    (void)n;
    Log("dettach shm done!", Debug) << "shmid: " << shmid << std::endl;

    // 最后删除共享资源
    n = shmctl(shmid, IPC_RMID, nullptr);
    assert(n != -1);
    (void)n;
    Log("delete shm done", Debug) << "shmid: " << shmid << std::endl;
    return 0;
}