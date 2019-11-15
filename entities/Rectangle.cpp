#include "Rectangle.hpp"

Rectangle::Rectangle(Rect *rect, Rect *screenRect, float alpha, int displacementX, int displacementY){
    this->rect = rect;
    this->frame = new Frame(
        VerticesFactory.initVertices(rect, screenRect, alpha);
        VerticesFactory.initDrawOrder();
    );
    this->displacementX = displacementX;
    this->displacementY = displacementY;
}

Rectangle::draw(){

}

Rectangle::update(){
    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);
}

Rectangle::~Rectangle(){
    delete this->rect;
    delete this->frame;
}
