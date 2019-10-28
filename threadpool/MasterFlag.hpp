#ifndef __MTASK__
#define __MTASK__

#include <pthread.h>

class MasterFlag{
private:
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int tasksDone, taskLimit;
public:
    MasterFlag(int taskLimit);
    ~MasterFlag();
    void reset(int taskLimit);
    void wait();
    void signal();
};

#endif