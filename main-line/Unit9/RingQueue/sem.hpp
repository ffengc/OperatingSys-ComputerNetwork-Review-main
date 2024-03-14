

#ifndef __YUFC_SEM_HPP__
#define __YUFC_SEM_HPP__

#include <iostream>
#include <semaphore.h>

class Sem
{
private:
    sem_t __sem; // 信号量
public:
    Sem(int value) { sem_init(&__sem, 0, value); }
    ~Sem() { sem_destroy(&__sem); }
    void p() { sem_wait(&__sem); }
    void v() { sem_post(&__sem); }
};

#endif