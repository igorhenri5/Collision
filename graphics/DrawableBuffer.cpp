#include "DrawableBuffer.hpp"

DrawableBuffer::DrawableBuffer(float *vertices, int verticeLength, short *drawOrder, int drawOrderLength){
    this->length = 2;
    this->drawableBuffers = new int[this->length];
    glGenBuffers(length, this->drawableBuffers);
    //setting vertices buffer id
    glBindBuffer(GL_ARRAY_BUFFER, this->drawableBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticeLength, vertices, GL_DYNAMIC_DRAW);
    //setting drawOrder buffer id
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->drawableBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort) * drawOrderLength, drawOrder, GL_STATIC_DRAW);
}

int DrawableBuffer::getVerticesId() {
    return this->drawableBuffers[0];
}

int DrawableBuffer::getDrawOrderId() {
    return this->drawableBuffers[1];
}

DrawableBuffer::~DrawableBuffer(){
    glDeleteBuffers(length, this->drawableBuffers);
    delete this->drawableBuffers;
}
