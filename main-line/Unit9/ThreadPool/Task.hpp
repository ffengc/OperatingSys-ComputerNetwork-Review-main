

#ifndef __YUFC_TASK_HPP__
#define __YUFC_TASK_HPP__

#include "Log.hpp"
#include <iostream>
#include <functional>

typedef std::function<int(int, int)> func_t;

class Task
{
public:
    int __x;
    int __y;
    func_t __func;
public:
    Task() {}
    Task(int x, int y, func_t func) : __x(x), __y(y), __func(func) {}
    void operator()(const std::string &name)
    {
        logMessage(NORMAL, "thread: %s, result: %d\n", name.c_str(), __func(__x, __y));
    }
};

#endif