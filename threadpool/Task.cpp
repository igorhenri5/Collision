#include "Task.hpp"
#include "AddTask.hpp"
#include "HandleCollisionTask.hpp"
#include "HandleCollisionTaskV2.hpp"

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

HandleCollisionTask::HandleCollisionTask(MasterFlag *masterFlag, QuadTree *quadtree, int rank, int threadNum): Task(masterFlag){
	this->quadtree	= quadtree;
	this->rank		= rank;
	this->threadNum	= threadNum;
}

void HandleCollisionTask::run(){
	this->quadtree->parallelHandleAllCollisions(this->rank, this->threadNum);
	this->masterFlag->signal();
}

HandleCollisionTaskV2::HandleCollisionTaskV2(MasterFlag *masterFlag, std::vector<QuadTree*> *quadTreeList, int rank, int threadNum, int numColisoes): Task(masterFlag){
	this->quadTreeList	= quadTreeList;
	this->rank		= rank;
	this->threadNum	= threadNum;
    this->numColisoes = numColisoes;
}

void HandleCollisionTaskV2::run(){
    int inicio, numColisoesThread;
    numColisoesThread = this->numColisoes / threadNum;
    inicio = this->rank * numColisoesThread;
    if(this->rank == threadNum - 1){
        numColisoesThread = numColisoes - this->rank * numColisoesThread;
    }
    for(int i = 0; numColisoesThread > 0 && i < this->quadTreeList->size(); i++){
        if(inicio < this->quadTreeList->at(i)->getNumberOfCollisions()){
            this->quadTreeList->at(i)->parallelHandleAllCollisionsV2(&inicio, &numColisoesThread);
        }
        else{
            inicio -= this->quadTreeList->at(i)->getNumberOfCollisions();
        }
    }
	this->masterFlag->signal();
}
