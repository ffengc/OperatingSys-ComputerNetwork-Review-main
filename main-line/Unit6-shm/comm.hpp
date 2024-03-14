

#pragma once

#include <iostream>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <cassert>
#include <unistd.h>
#include <string.h>
#include "Log.hpp"

// 这些都可以随便写，只要保证这个路径是有可以访问的权限即可
#define PATH_NAME "/home/yufc"
#define PROJ_ID 0x66
#define SHM_SIZE 4096 // 共享内存的大小，最好是页（PAGE: 4096）的整数倍