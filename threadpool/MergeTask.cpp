#include "MergeTask.hpp"

MergeTask::MergeTask(MasterFlag *masterFlag, std::vector<MyRectangle*> *rectanleList, std::vector<int> *flagList,
                thrust::device_vector<int> *keys, thrust::device_vector<int> *values, int begin) : Task(masterFlag){
	this->rectanleList	= rectanleList;
	this->flagList 	= flagList;
	this->keys   	= keys;
	this->values	= values;
	this->begin 	= begin;
}

void MergeTask::run(){
/*	
  for(int i = 0; i < this->rectanleList->size(); i++){
		keys[(i + begin)] = (int) this->rectanleList[i];
		values[(i + begin)] = this->flagList[i];
	}
  */
	this->masterFlag->signal();
}
