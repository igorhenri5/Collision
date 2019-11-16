#include "DrawableBuffer.hpp"

DrawableBuffer::DrawableBuffer(GLfloat *vertices, int verticeLength, GLshort *drawOrder, int drawOrderLength){
    this->length = 2;
    this->buffers = new GLuint[this->length];
    glGenBuffers(length, this->buffers);
    //setting vertices buffer id
    glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticeLength, vertices, GL_DYNAMIC_DRAW);
    //setting drawOrder buffer id
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort) * drawOrderLength, drawOrder, GL_STATIC_DRAW);
}

unsigned int DrawableBuffer::getVerticesId() {
    return this->buffers[0];
}

unsigned int DrawableBuffer::getDrawOrderId() {
    return this->buffers[1];
}

DrawableBuffer::~DrawableBuffer(){
    glDeleteBuffers(length, this->buffers);
    delete this->buffers;
}
