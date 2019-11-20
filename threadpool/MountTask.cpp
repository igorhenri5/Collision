#include "MountTask.hpp"

MountTask::MountTask(MasterFlag *masterFlag, QuadTree *quadtree, int rank, int threadNum, std::vector<std::pair<MyRectangle*, MyRectangle*>> *pairList): Task(masterFlag){
	this->quadtree	= quadtree;
	this->rank		= rank;
	this->threadNum	= threadNum;
	this->pairList	= pairList;
}

void MountTask::run(){
	this->quadtree->parallelMountAllCollisionPairList(this->rank, this->threadNum, this->pairList);
	this->masterFlag->signal();
}
