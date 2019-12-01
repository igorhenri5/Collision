
#ifndef __MERGETASK__
#define __MERGETASK__

#include <vector>
#include <thrust/device_vector.h>

#include "Task.hpp"
#include "../entities/Rectangle.hpp"

class MergeTask : public Task{
private:
    std::vector<MyRectangle*> *rectanleList;
    std::vector<int> *flagList;
    thrust::device_vector<int> *keys, *values;
    int begin;
public:
    MergeTask(MasterFlag *masterFlag, std::vector<MyRectangle*> *rectanleList, std::vector<int> *flagList,
    			 thrust::device_vector<int> *keys, thrust::device_vector<int> *values, int begin);
    void run();
};

#endif
