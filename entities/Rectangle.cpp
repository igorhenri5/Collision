#include "Rectangle.hpp"

Rectangle::Rectangle(Rect *rect, Rect *screenRect, float alpha){
    this->rect = rect;
    this->frame = new Frame(
        VerticesFactory.initVertices(rect, screenRect, alpha);
        VerticesFactory.initDrawOrder();
    );
}

Rectangle::draw(){

}

Rectangle::update(){

}

Rectangle::~Rectangle(){
    delete this->rect;
    delete this->frame;
}
