#include "ThreadPool.hpp"

void* ThreadPool::threadRun(void* param){
    Task *task;
    SynchronizedQueue *workQueue;
    workQueue = reinterpret_cast<SynchronizedQueue *>(param);
    task = workQueue->pop();
    while(task != NULL){
        task->run();
        task = workQueue->pop();
    }
    return NULL;
}

ThreadPool::ThreadPool(int size){
    this->size = size;
    this->pool = new pthread_t[size];
    this->workQueue = new SynchronizedQueue();
    for(int i = 0; i < this->size; i++){
        if(!pthread_create(&(this->pool[i]), NULL, this->threadRun,(void*)this->workQueue)){
          //cout << "thread"  << i << endl;
        }
    }
}

ThreadPool::~ThreadPool(){
    for (int i=0 ; i<this->size; i++)
        this->workQueue->push(NULL);
    for(int i = 0; i < this->size; i++)
        pthread_join(this->pool[i], NULL);
    delete this->workQueue;
    delete this->pool;
}

void ThreadPool::addTask(Task* task){
    workQueue->push(task);
}

int ThreadPool::getSize(){
    return this->size;
}