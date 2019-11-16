#include "Frame.hpp"

Frame::Frame(float *vertices, int verticeLength, short *drawOrder, int drawOrderLength){
    this->vertices = vertices;
    this->drawOrder = drawOrder;
    // this->drawableBuffer = new DrawableBuffer(vertices, verticeLength, drawOrder, drawOrderLength);
}

float* Frame::getVertices(){
    return this->vertices;
}

short* Frame::getDrawOrder(){
    return this->drawOrder;
}

DrawableBuffer* Frame::getDrawableBuffer(){
    return this->drawableBuffer;
}

Frame::~Frame(){
    delete this->vertices;
    delete this->drawOrder;
    delete this->drawableBuffer;
}
