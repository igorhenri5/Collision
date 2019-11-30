#include "MergeTask.hpp"

MergeTask::MergeTaskMergeTask(MasterFlag *masterFlag, std::vector<MyRectangle*> *rectanleList, std::vector<bool> *flagList,
    			 thrust::device_vector<int> *keys, thrust::device_vector<bool> *values, int begin) : Task(masterFlag){
	this->rectanleList	= rectanleList;
	this->flagList 	= flagList;
	this->keys   	= keys;
	this->values	= values;
	this->begin 	= begin;
}

void MergeTask::run(){
	for(int i = 0; i < this->rectanleList->size();  i++){
		keys->at(i + begin) = this->rectanleList->at(i);
		values->at(i + begin) = this->flagList->at(i);
	}
	this->masterFlag->signal();
}

