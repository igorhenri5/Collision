#ifndef __TPOOL__
#define __TPOOL__

#include <pthread.h>
#include "SynchronizedQueue.hpp"

class ThreadPool{
private:
    pthread_t *pool;
    SynchronizedQueue *workQueue;

    static void* threadRun(void *);
public:
    ThreadPool(int size);
    ~ThreadPool();
    void addTask(Task* task);
    int getSize();
    int size;
};

#endif