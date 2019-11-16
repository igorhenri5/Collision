#include "Frame.hpp"

Frame::Frame(float *vertices, short *drawOrder){
    this->vertices = vertices;
    this->drawOrder = drawOrder;
}

float* Frame::getVertices(){
    return this->vertices;
}

short* Frame::getDrawOrder(){
    return this->drawOrder;
}

Frame::~Frame(){
    delete this->vertices;
    delete this->drawOrder;
}
