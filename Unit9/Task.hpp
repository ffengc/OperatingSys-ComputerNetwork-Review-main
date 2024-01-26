

#ifndef __YUFC_TASK__
#define __YUFC_TASK__

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
    int operator()() { return __func(__x, __y); }
};

#endif