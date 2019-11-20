#ifndef __UPDATETASK__
#define __UPDATETASK__

#include "Task.hpp"
#include "../quadtree/Quadtree.hpp"
#include "../entities/Rectangle.hpp"

class UpdateTask : public Task{
private:
	QuadTree *quadtree;
    int rank, threadNum;
public:
    UpdateTask(MasterFlag *masterFlag, QuadTree *quadtree, int rank, int threadNum);
    void run();
};

#endif
