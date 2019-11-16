#include "Rectangle.hpp"

MyRectangle::MyRectangle(Rect *rect, Rect *screenRect, float alpha, int displacementX, int displacementY, ProgramFactory *programFactory){
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

    this->programFactory = programFactory;
}

void MyRectangle::draw(){
    GlUtil::draw(programFactory->getProgram(), this->programParams);
}

void MyRectangle::update(){
    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);
}

MyRectangle::~MyRectangle(){
    delete this->mvp;
    delete this->rect;
    delete this->frame;
    delete this->programParams;
}
