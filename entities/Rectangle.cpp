#include "Rectangle.hpp"

MyRectangle::MyRectangle(Rect *rect, Rect *screenRect, int displacementX, int displacementY){
    this->rect = rect;
    this->screenRect = screenRect;

    //init displacement
    this->displacementX = displacementX;
    this->displacementY = displacementY;

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

void MyRectangle::handleCollision(MyRectangle *rectangle){

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

    if(rectA.intersect(&rectB)){
        this->collidedFlag = 1;
        rectangle->setCollidedFlag(1);
    }
}

void MyRectangle::draw(){
    //Não utilizado nessa versão
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
    delete this->rect;
}
