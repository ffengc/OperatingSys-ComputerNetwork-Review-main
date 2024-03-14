
#include "comm.hpp"

void ReadFromIpc()
{
    // 1. 创建管道文件
    if (mkfifo(ipcPath.c_str(), MODE) < 0)
    {
        // 创建管道文件失败
        perror("mkfifo");
        exit(-1);
    }
    // 2. 正常的文件操作
    int fd = open(ipcPath.c_str(), O_RDONLY);
    assert(fd >= 0); // 文件打开失败
    // 3. 开始通信
    // 读文件
    char buffer[SIZE];
    while (true)
    {
        memset(buffer, '\0', sizeof(buffer)); // 先把读取的缓冲区设置为0
        ssize_t s = read(fd, buffer, sizeof(buffer) - 1);
        // 最好不要让缓冲区写满，因为没有\0
        if (s > 0)
        {
            // 读到客户端的字符串了
            std::cout << "client say: " << buffer << std::endl;
        }
        else if (s == 0)
        {
            // 写端关闭了文件描述符
            std::cerr << "client quit, server quit too" << std::endl;
            break;
        }
        else
        {
            perror("read");
            break; // 读取有问题
        }
    }
    close(fd);
}

int main()
{
    ReadFromIpc();
    return 0;
}