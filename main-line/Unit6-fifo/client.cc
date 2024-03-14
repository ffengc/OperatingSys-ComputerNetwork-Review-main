
#include "comm.hpp"

void WriteToIpc()
{
    // 1. 获取管道文件
    int fd = open(ipcPath.c_str(), O_WRONLY); // 按照写的方式打开
    assert(fd >= 0);
    // 2. ipc过程
    // 把数据写到管道中去
    std::string buffer;
    while (true)
    {
        std::cout << "Please Enter the mesg: ";
        std::getline(std::cin, buffer);
        write(fd, buffer.c_str(), buffer.size());
    }
    // 3. 关闭
    close(fd);
}
int main()
{
    WriteToIpc();
    return 0;
}