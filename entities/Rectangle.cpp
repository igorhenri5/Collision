#include "Rectangle.hpp"

MyRectangle::MyRectangle(Rect *rect, Rect *screenRect, int displacementX, int displacementY){
    this->rect = rect;
    this->screenRect = screenRect;

    //init displacement
    this->displacementX = displacementX;
    this->displacementY = displacementY;

    //pthread_mutex_init(&this->mutex, 0);
    this->collidedFlag = 0;
}

Rect* MyRectangle::getRect(){
    return this->rect;
}
void MyRectangle::setRect(Rect* rect){
    this->rect = rect;
}

int MyRectangle::getDisplacementX(){
    return this->displacementX;
}

void MyRectangle::setDisplacementX(int val){
    this->displacementX = val;
}

int MyRectangle::getDisplacementY(){
    return this->displacementY;
}

void MyRectangle::setDisplacementY(int val){
    this->displacementY = val;
}

int MyRectangle::getCollidedFlag(){
    return this->collidedFlag;
}

void MyRectangle::setCollidedFlag(int val){
    this->collidedFlag = val;
}
/*
pthread_mutex_t* MyRectangle::getMutex(){
    return &this->mutex;
}
*/
bool MyRectangle::handleCollision(MyRectangle *rectangle){
    Rect rectA(
        this->rect->getX() + this->displacementX,
        this->rect->getY() + this->displacementY,
        this->rect->getWidth(),
        this->rect->getHeight()
    );
    Rect rectB(
        rectangle->getRect()->getX() + rectangle->getDisplacementX(),
        rectangle->getRect()->getY() + rectangle->getDisplacementY(),
        rectangle->getRect()->getWidth(),
        rectangle->getRect()->getHeight()
    );

    // if(rectA.intersect(&rectB)){
    //     this->collidedFlag = 1;
    //     rectangle->setCollidedFlag(1);
    // }

    return rectA.intersect(&rectB);

}

//se deu colisão = this->col

void MyRectangle::draw(){
    // std::cout << "draw rect" << std::endl;
    // std::cout << this->programFactory->getProgram() << std::endl;
}

void MyRectangle::update(){

    if(this->collidedFlag){
        this->displacementY *= -1;
        this->displacementX *= -1;
    }

    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);

}

MyRectangle::~MyRectangle(){
    //pthread_mutex_destroy(&this->mutex);
    delete this->rect;
}
