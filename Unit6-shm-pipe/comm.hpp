#pragma once

#include <iostream>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <cassert>
#include <string>
#include "Log.hpp"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 这里这些和原来是一样的
#define PATH_NAME "/home/yufc"
#define PROJ_ID 0x66
#define SHM_SIZE 4096

#define FIFO_NAME "./fifo"

class Init
{
public:
    Init()
    {
        umask(0);
        // 创建一个管道文件，用于唤醒
        int n = mkfifo(FIFO_NAME, 0666);
        assert(n == 0);
        (void)n;
        Log("create fifo success", Notice) << std::endl;
    }
    ~Init()
    {
        // 删除管道文件
        unlink(FIFO_NAME);
        Log("rm fifo success", Notice) << std::endl;
    }
};

#define READ O_RDONLY
#define WRITE O_WRONLY

int openFIFO(std::string path_name, int flags)
{
    // path_name就是管道文件的路径
    int fd = open(path_name.c_str(), flags);
    assert(fd > 0);
    return fd;
}
void WaitFIFO(int fd)
{
    // 等待管道文件里面的mesg
    Log("wait...", Notice) << std::endl;
    uint32_t temp = 0;
    ssize_t s = read(fd, &temp, sizeof(uint32_t));
    assert(s == sizeof(uint32_t));
    (void)s;
}
void Signal(int fd)
{
    // 唤醒
    Log("wake up ...", Notice) << std::endl;
    uint32_t temp = 1;
    ssize_t s = write(fd, &temp, sizeof(uint32_t)); // 往管道里面写入一个数字
    assert(s == sizeof(uint32_t));
    (void)s;
}
void CloseFIFO(int fd)
{
    close(fd);
}