#include "Frame.hpp"

Frame::Frame(float *vertices, int verticeLength, GLuint *drawOrder, int drawOrderLength){
    this->vertices = vertices;
    this->drawOrder = drawOrder;
    this->drawableBuffer = new DrawableBuffer(vertices, verticeLength, drawOrder, drawOrderLength);
}

GLfloat* Frame::getVertices(){
    return this->vertices;
}

GLuint* Frame::getDrawOrder(){
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
