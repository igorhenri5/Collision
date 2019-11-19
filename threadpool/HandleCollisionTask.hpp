#ifndef __TASKS__
#define __TASKS__

#include "Task.hpp"
#include "../entities/Rectangle.hpp"

class HandleCollisionTask : public Task{
private:
	MyRectangle* rectangle;
    std::vector<MyRectangle*>::iterator begin, end;
public:
    HandleCollisionTask(MasterFlag*, MyRectangle*, std::vector<MyRectangle*>::iterator, std::vector<MyRectangle*>::iterator);
    void run();
};

#endif