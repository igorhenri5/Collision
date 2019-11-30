
#ifndef __MERGETASK__
#define __MERGETASK__

#include <vector>
#include <thrust/device_vector.h>

#include "Task.hpp"
#include "Rectangle.hpp"

class MergeTask : public Task{
private:
public:
    MergeTask(MasterFlag *masterFlag, std::vector<MyRectangle*> *rectanleList, std::vector<bool> *flagList,
    			 thrust::device_vector<int> *keys, thrust::device_vector<bool> *values, int begin);
    void run();
};

#endif