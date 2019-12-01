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
	std::vector<MyRectangle *> *rectangleList;
	std::vector<int> *flagList;
public:
    HandleCollisionTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<MyRectangle *> *rectangleList,
							std::vector<int> *flagList, int rank, int threadNum);
    void run();
};

#endif
