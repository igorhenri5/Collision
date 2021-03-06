#include "DrawableBuffer.hpp"
#include <iostream>

DrawableBuffer::DrawableBuffer(GLfloat *vertices, int verticesLength, GLuint *drawOrder, int drawOrderLength){
    this->verticesLength = verticesLength;
    this->drawOrderLength = drawOrderLength;
    this->length = 2;
    this->buffers = new GLuint[2];
    glGenBuffers(2, this->buffers);

    //setting vertices buffer id
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesLength, vertices, GL_DYNAMIC_DRAW);
    //setting drawOrder buffer id
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * drawOrderLength, drawOrder, GL_STATIC_DRAW);
}

unsigned int DrawableBuffer::getVerticesId() {
    return this->buffers[0];
}

unsigned int DrawableBuffer::getDrawOrderId() {
    return this->buffers[1];
}

int DrawableBuffer::getVerticesLength(){
    return this->verticesLength;
}

int DrawableBuffer::getDrawOrderLength(){
    return this->drawOrderLength;
}

DrawableBuffer::~DrawableBuffer(){
    glDeleteBuffers(length, this->buffers);
    delete this->buffers;
}
