#include "Task.hpp"

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


CollisionCheckTask::CollisionCheckTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<IDrawable *>::iterator begin, std::vector<IDrawable *>::iterator end) : Task(masterFlag){
	this->quadtree	= quadtree;
	this->begin 	= begin;
	this->end   	= end;
}

void CollisionCheckTask::run(){

}

