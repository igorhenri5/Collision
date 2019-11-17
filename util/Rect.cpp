#include "Rect.hpp"

Rect::Rect(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int Rect::getX(){
    return this->x;
}

int Rect::getY(){
    return this->y;
}

int Rect::getWidth(){
    return this->width;
}

int Rect::getHeight(){
    return this->height;
}

void Rect::setX(int x){
    this->x = x;
}

void Rect::setY(int y){
    this->y = y;
}

bool Rect::intersect(Rect *rect){
    return (this->x < rect->getX() + rect->getWidth()
            && this->x + this->width > rect->getX()
            && this->y + this->height > rect->getY()
            && this->y < rect->getY() + rect->getHeight());
}
