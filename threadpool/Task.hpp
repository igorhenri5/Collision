#ifndef __TASKS__
#define __TASKS__

#include <vector>
#include "MasterFlag.hpp"
#include "../quadtree/Quadtree.hpp"
#include "../drawable/IDrawable.hpp"
#include "../entities/Rectangle.hpp"

class Task{
protected:
    MasterFlag *masterFlag;
public:
    Task(MasterFlag *masterFlag);
    virtual ~Task();
    virtual void run() = 0;
};

class AddTask : public Task{
private:
	QuadTree *quadtree;
    std::vector<IDrawable *>::iterator begin, end;
public:
    AddTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<IDrawable *>::iterator begin, std::vector<IDrawable *>::iterator end);
    void run();
};

class HandleCollisionTask : public Task{
private:
	QuadTree *quadtree;
    std::vector<IDrawable *>::iterator begin, end;
public:
    HandleCollisionTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<IDrawable *>::iterator begin, std::vector<IDrawable *>::iterator end);
    void run();
};


#endif
