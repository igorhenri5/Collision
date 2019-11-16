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
    this->mvp = new float[this->mvpHeight * this->mvpWidth];
    MatrixM::identity(this->mvp, this->mvpWidth, this->mvpHeight);
    this->programParams = new ProgramParams(this->frame->getDrawableBuffer(), this->mvp);
}

void Rectangle::draw(){

}

void Rectangle::update(){
    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);
}

Rectangle::~Rectangle(){
    delete this->mvp;
    delete this->rect;
    delete this->frame;
    delete this->programParams;
}
