#ifndef __SQUEUE__
#define __SQUEUE__

#include <pthread.h>
#include <queue>
#include "Task.hpp"

class SynchronizedQueue{
private:
    std::queue<Task*> *taskQueue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
public:
    SynchronizedQueue();
    ~SynchronizedQueue();
    void push(Task* task);
    Task* pop();
};

#endif