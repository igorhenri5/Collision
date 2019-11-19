#ifndef __ADDTASK__
#define __ADDTASK__

#include "Task.hpp"
#include "../quadtree/Quadtree.hpp"
#include "../drawable/IDrawable.hpp"

class AddTask : public Task{
private:
	QuadTree *quadtree;
    std::vector<IDrawable *>::iterator begin, end;
public:
    AddTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<IDrawable *>::iterator begin, std::vector<IDrawable *>::iterator end);
    void run();
};

#endif