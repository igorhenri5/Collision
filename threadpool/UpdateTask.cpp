#include "UpdateTask.hpp"

UpdateTask::UpdateTask(MasterFlag *masterFlag, QuadTree *quadtree, int rank, int threadNum): Task(masterFlag){
	this->quadtree	= quadtree;
	this->rank		= rank;
	this->threadNum	= threadNum;
}

void UpdateTask::run(){
	this->quadtree->parallelUpdateAll(this->rank, this->threadNum);
	this->masterFlag->signal();
}
