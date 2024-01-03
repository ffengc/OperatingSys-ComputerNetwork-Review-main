
#include "comm.hpp"

void start()
{
    Log("child pid is: ", Debug) << getpid() << std::endl;
    key_t k = ftok(PATH_NAME, PROJ_ID); // 生成一个唯一的共享内存的key
    if (k < 0)
    {
        Log("create key failed!", Error) << " client key: " << k << std::endl;
        exit(1); // 直接退出就行了
    }
    Log("create key success!", Debug) << " client key: " << k << std::endl;
    // 获取共享内存
    int shmid = shmget(k, SHM_SIZE, IPC_CREAT);
    if (shmid < 0)
    {
        Log("create shm failed", Error) << " shmid: " << shmid << std::endl;
        exit(2);
    }
    Log("create shm success", Debug) << " shmid: " << shmid << std::endl;
    // 把获取到的共享内存映射到自己的虚拟内存上
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    if (shmaddr == nullptr)
    {
        Log("attach shm failed", Error)
            << " client key: " << k
            << " shmid: " << shmid << std::endl;
        exit(3);
    }
    Log("attach shm success", Debug)
        << " client key: " << k
        << " shmid: " << shmid << std::endl;

    // 开始通信
    int fd = openFIFO(FIFO_NAME, WRITE); // 先找到已经创建好的管道，并打开
    while (true)
    {
        ssize_t s = read(0, shmaddr, SHM_SIZE - 1);
        if (s > 0)
        {
            // 说明读到了
            shmaddr[s - 1] = 0;
            Signal(fd); // 唤醒对方
            if (strcmp(shmaddr, "quit") == 0)
                break;
        }
    }
    CloseFIFO(fd);
    // detach
    int n = shmdt(shmaddr);
    assert(n != -1);
    Log("detach shm success", Debug) << " client key: " << std::endl;
    // client不用删除shm内存，是server做的事
}

int main()
{
    start();
    return 0;
}