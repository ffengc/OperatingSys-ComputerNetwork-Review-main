

#ifndef __YUFC_LOG_HPP__
#define __YUFC_LOG_HPP__

// 日志是有日志级别的
// 不同的级别代表不同的响应方式

#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4

#include <string>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

const char *gLevelMap[] = {
    "DEBUG",
    "NORMAL",
    "WARNING",
    "ERROR",
    "FATAL"};

#define LOGFILE "./threadpool.log"

void logMessage(int level, const char *format, ...)
{
#ifdef __DEBUG_SHOW
    if (level == DEBUG)
        return;
#else
    char stdBuffer[1024];
    time_t timestamp = time(nullptr);
    snprintf(stdBuffer, sizeof stdBuffer, "[%s] [%ld] ", gLevelMap[level], timestamp);
    char logBuffer[1024]; // 自定义部分
    va_list args;
    va_start(args, format);                               // 初始化一下
    vsnprintf(logBuffer, sizeof logBuffer, format, args); // 可以直接格式化到字符串中来
    va_end(args);
#endif
    FILE *fp = fopen(LOGFILE, "a");
    fprintf(fp, "%s%s", stdBuffer, logBuffer);
    fclose(fp);
}

#endif