#include "Rectangle.hpp"

Rectangle::Rectangle(Rect *rect, Rect *screenRect, float alpha, int displacementX, int displacementY){
    int vertcesLegth, drawOrderLength;
    this->rect = rect;
    this->frame = new Frame(
        VerticesFactory::initVertices(&vertcesLegth, rect, screenRect, alpha),
        VerticesFactory::initDrawOrder(&drawOrderLength)
    );
    this->displacementX = displacementX;
    this->displacementY = displacementY;
}

void Rectangle::draw(){

}

void Rectangle::update(){
    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);
}

Rectangle::~Rectangle(){
    delete this->rect;
    delete this->frame;
}
