#include "Rectangle.hpp"

Rectangle::Rectangle(Rect *rect, Rect *screenRect, float alpha, int displacementX, int displacementY){
    int vertcesLegth, drawOrderLength;
    this->rect = rect;
    this->frame = new Frame(
        VerticesFactory::initVertices(&vertcesLegth, rect, screenRect, alpha),
        vertcesLegth,
        VerticesFactory::initDrawOrder(&drawOrderLength),
        drawOrderLength
    );
    this->displacementX = displacementX;
    this->displacementY = displacementY;
    this->mvpWidth = 4;
    this->mvpHeight = 4;
    this->mvp = new float*[this->mvpHeight];
    for(int i = 0; i < this->mvpHeight; i++){
        this->mvp[i] = new float[this->mvpWidth];
    }
    MatrixM::identity(this->mvp, this->mvpWidth, this->mvpHeight);
}

void Rectangle::draw(){

}

void Rectangle::update(){
    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);
}

Rectangle::~Rectangle(){
    for(int i = 0; i < this->mvpHeight; i++){
        delete this->mvp[i];
    }
    delete this->mvp;
    delete this->rect;
    delete this->frame;
}
