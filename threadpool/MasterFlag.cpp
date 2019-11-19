#include "MasterFlag.hpp"

MasterFlag::MasterFlag(int taskLimit){
    pthread_mutex_init(&this->mutex, 0);
    pthread_cond_init(&this->cond, 0);
    tasksDone = 0;
    this->taskLimit = taskLimit;
}

MasterFlag::~MasterFlag(){
    pthread_mutex_destroy(&this->mutex);
    pthread_cond_destroy(&this->cond);
}

void MasterFlag::reset(int taskLimit){
    this->tasksDone = 0;
    this->taskLimit = taskLimit;
}

void MasterFlag::increaseTaskNum(int increaseAmount){
    pthread_mutex_lock(&this->mutex);
    taskLimit += increaseAmount;
    pthread_mutex_unlock(&this->mutex);
}

void MasterFlag::wait(){
    pthread_mutex_lock(&this->mutex);
    if(this->tasksDone < this->taskLimit)
        pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&this->mutex);
}

void MasterFlag::signal(){
    pthread_mutex_lock(&this->mutex);
    this->tasksDone++;
    if(this->tasksDone == this->taskLimit){
        pthread_cond_signal(&this->cond);
    }
    pthread_mutex_unlock(&this->mutex);
}