

#include "comm.hpp"

int main()
{
    Log("child pid is: ", Debug) << getpid() << std::endl;
    key_t k = ftok(PATH_NAME, PROJ_ID);
    // 生成一个key
    if (k < 0)
    {
        Log("create key failed", Error) << "client key: " << k << std::endl;
        exit(1);
    }
    Log("create key done!", Debug) << "client key: " << k << std::endl;
    // 获取共享内存
    int shmid = shmget(k, SHM_SIZE, IPC_CREAT);
    if (shmid < 0)
    {
        Log("create shm failed", Error) << " client key: " << k << std::endl;
        exit(2);
    }
    Log("create shm success", Debug) << " client key: " << k << std::endl;
    // attach
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    if (shmaddr == nullptr)
    {
        Log("attach shm failed", Error) << "client key: " << k << std::endl;
        exit(3);
    }
    Log("attach shm success", Debug) << " client key: " << k << std::endl;
    // 通信
    while (1)
    {
        ssize_t s = read(0, shmaddr, SHM_SIZE - 1); // 从键盘读取字符串
        if (s > 0)
        {
            shmaddr[s - 1] = 0; // 字符串的 \0
            if (strcmp(shmaddr, "quit") == 0)
                break; // 如果输入quit就退出客户端
        }
    }
    // dettach
    int n = shmdt(shmaddr);
    assert(n != -1);
    Log("detach shm success", Debug) << "client key: " << k << std::endl;

    // client要不要删除shm呢？
    // server删除就行了！
    // client只负责用，只负责attach上然后用，用完dettach就行了，其他不用管！
    return 0;
}