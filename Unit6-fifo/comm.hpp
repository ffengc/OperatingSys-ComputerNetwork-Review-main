
#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define MODE 0666 // 定义管道文件的权限
#define SIZE 128
std::string ipcPath = "./fifo.ipc";
#endif