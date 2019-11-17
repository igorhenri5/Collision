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


bool Rect::isAllBoundsInside(Rect *rect){

}
