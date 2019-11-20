#include "Task.hpp"
#include "AddTask.hpp"
#include "HandleCollisionTask.hpp"

Task::Task(MasterFlag *masterFlag){
    this->masterFlag = masterFlag;
}

Task::~Task(){}

AddTask::AddTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<IDrawable *>::iterator begin, std::vector<IDrawable *>::iterator end) : Task(masterFlag){
	this->quadtree	= quadtree;
	this->begin 	= begin;
	this->end   	= end;
}

void AddTask::run(){
	for (auto drawable = begin; drawable != end; ++drawable){
		this->quadtree->addParallel((MyRectangle *)(*drawable));
    }
	this->masterFlag->signal();
}


HandleCollisionTask::HandleCollisionTask(MasterFlag* masterFlag, std::vector<std::pair<MyRectangle*, MyRectangle*>>::iterator begin, std::vector<std::pair<MyRectangle*, MyRectangle*>>::iterator end) : Task(masterFlag){
	this->begin 	= begin;
	this->end   	= end;
}

void HandleCollisionTask::run(){
	for (auto pair = begin; pair != end; ++pair){
		(*pair).first->handleCollision((*pair).second);
    }
	this->masterFlag->signal();
}
