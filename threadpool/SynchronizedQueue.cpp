#include "SynchronizedQueue.hpp"

SynchronizedQueue::SynchronizedQueue(){
    this->taskQueue = new std::queue<Task*>();
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);
}

SynchronizedQueue::~SynchronizedQueue(){
    while (!this->taskQueue->empty()){
      delete this->taskQueue->front();
        this->taskQueue->pop();
    }
    delete this->taskQueue;

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void SynchronizedQueue::push(Task* task){
    pthread_mutex_lock(&mutex);
    this->taskQueue->push(task);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

Task* SynchronizedQueue::pop(){
    Task* task = 0;
    pthread_mutex_lock(&mutex);

    while(this->taskQueue->empty())
      pthread_cond_wait(&cond, &mutex);

    task = this->taskQueue->front();
    this->taskQueue->pop();

    pthread_mutex_unlock(&mutex);
    return task;
}