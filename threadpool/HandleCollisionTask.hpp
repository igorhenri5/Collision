#ifndef __TASKS__
#define __TASKS__

#include "Task.hpp"
#include <utility>
#include "../entities/Rectangle.hpp"

class HandleCollisionTask : public Task{
private:
    std::vector<std::pair<MyRectangle*, MyRectangle*>>::iterator begin, end;
public:
    HandleCollisionTask(MasterFlag*, std::vector<std::pair<MyRectangle*, MyRectangle*>>::iterator, std::vector<std::pair<MyRectangle*, MyRectangle*>>::iterator);
    void run();
};

#endif