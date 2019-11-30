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

HandleCollisionTask::HandleCollisionTask(MasterFlag *masterFlag, QuadTree *quadtree, std::vector<MyRectangle *> *rectangleList,
                                            std::vector<bool> *flagList, int rank, int threadNum): Task(masterFlag){
	this->quadtree	= quadtree;
    this->rectangleList	= rectangleList;
    this->flagList	= flagList;
	this->rank		= rank;
	this->threadNum	= threadNum;
}

void HandleCollisionTask::run(){
	this->quadtree->parallelHandleAllCollisions(this->rectangleList, this-> flagList,this->rank, this->threadNum);
	this->masterFlag->signal();
}
