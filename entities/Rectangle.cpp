#include "Rectangle.hpp"
#include <iostream>

MyRectangle::MyRectangle(Rect *rect, Rect *screenRect, float alpha, int displacementX, int displacementY, ProgramFactory *programFactory){
    int vertcesLegth, drawOrderLength;
    GLfloat *vertices;
    GLuint *drawOrder;
    this->rect = rect;
    vertices = VerticesFactory::initVertices(&vertcesLegth, rect, screenRect, alpha);
    drawOrder = VerticesFactory::initDrawOrder(&drawOrderLength);
    this->frame = new Frame(vertices, vertcesLegth, drawOrder, drawOrderLength);

    this->displacementX = displacementX;
    this->displacementY = displacementY;

    this->mvpWidth = 4;
    this->mvpHeight = 4;
    this->mvp = new float[this->mvpHeight * this->mvpWidth];
    MatrixM::identity(this->mvp, this->mvpWidth, this->mvpHeight);


    for(int j = 0; j < 6; j++){
        std::cout << drawOrder[j] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            std::cout << vertices[i*3 + j] << " ";
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << this->mvp[i*4 + j] << " ";
        }
        std::cout << std::endl;
    }

    this->programParams = new ProgramParams(this->frame->getDrawableBuffer(), this->mvp);

    this->programFactory = programFactory;
}

Rect* MyRectangle::getRect(){
    return this->rect;
}
Frame* MyRectangle::getFrame(){
    return this->frame;
}

void MyRectangle::setRect(Rect* rect){
    this->rect = rect;
}

void MyRectangle::setFrame(Frame* frame){
    this->frame = frame;
}


void MyRectangle::draw(){
    // std::cout << "draw rect" << std::endl;
    std::cout << this->programFactory->getProgram() << std::endl;
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
