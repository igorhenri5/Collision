#ifndef __HCLTASKV2__
#define __HCLTASKV2__

#include "Task.hpp"
#include <vector>
#include "../quadtree/QuadTree.hpp"

class HandleCollisionTaskV2 : public Task{
private:
	std::vector<QuadTree*> *quadTreeList;
    int rank, threadNum, numColisoes;
public:
    HandleCollisionTaskV2(MasterFlag *masterFlag, std::vector<QuadTree*> *quadTreeList, int rank, int threadNum, int numColisoes);
    void run();
};

#endif
