#ifndef __HCLTASK__
#define __HCLTASK__

#include "Task.hpp"
#include <vector>
#include "../entities/Rectangle.hpp"
#include "../quadtree/QuadTree.hpp"

class HandleCollisionTask : public Task{
private:
	QuadTree *quadtree;
    int rank, threadNum;
public:
    HandleCollisionTask(MasterFlag *masterFlag, QuadTree *quadtree, int rank, int threadNum);
    void run();
};

#endif
