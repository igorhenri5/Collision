#ifndef __TASKS__
#define __TASKS__

#include <vector>
#include "MasterFlag.hpp"

class Task{
protected:
    MasterFlag *masterFlag;
public:
    Task(MasterFlag *masterFlag);
    virtual ~Task();
    virtual void run() = 0;
};

#endif
