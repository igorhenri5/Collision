#ifndef __MOUNTTASK__
#define __MOUNTTASK__

#include "Task.hpp"
#include "../quadtree/QuadTree.hpp"
#include <vector>
#include "../entities/Rectangle.hpp"

class MountTask : public Task{
private:
	QuadTree *quadtree;
    int rank, threadNum;
    std::vector<std::pair<MyRectangle*, MyRectangle*>> *pairList;
public:
    MountTask(MasterFlag *masterFlag, QuadTree *quadtree, int rank, int threadNum, std::vector<std::pair<MyRectangle*, MyRectangle*>> *pairList);
    void run();
};

#endif
