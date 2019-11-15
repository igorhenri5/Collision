#include "Frame.hpp"

Frame::Frame(float *vertices, short *drawOrder){
    this->vertices = vertices;
    this->drawOrder= drawOrder;
}

float* getVertices(){
    return this->vertices;
}

short* getDrawOrder(){
    return this->drawOrder;
}

Frame::~Frame(){
    delete this->vertices;
    delete this->drawOrder;
}
