#include "Rect.hpp"

Rect::Rect(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int getX(){
    return this->x;
}
int getY(){
    return this->y;
}
int getWidth(){
    return this->width;
}
int getHeight(){
    return this->height;
}
