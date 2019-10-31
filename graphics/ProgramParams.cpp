#include "ProgramParams.hpp"

ProgramParams::ProgramParams(DrawableBuffer *drawableBuffer, int verticesLength, int drawOrderLength, float *mvpMatrix) {
    this->drawableBuffer = drawableBuffer;
    this->verticesLength = verticesLength;
    this->drawOrderLength = drawOrderLength;
    this->mvpMatrix = mvpMatrix;
}

float* ProgramParams::getMvpMatrix(){
    return this->mvpMatrix;
}

void ProgramParams::setMvpMatrix(float* mvpMatrix) {
    this->mvpMatrix = mvpMatrix;
}

DrawableBuffer* ProgramParams::getDrawableBuffer() {
    return this->drawableBuffer;
}

void ProgramParams::setDrawableBuffer(DrawableBuffer *drawableBuffer) {
    this->drawableBuffer = drawableBuffer;
}

int ProgramParams::getVerticesLength() {
    return this->verticesLength;
}

void ProgramParams::setVerticesLength(int verticesLength) {
    this->verticesLength = verticesLength;
}

int ProgramParams::getDrawOrderLength() {
    return this->drawOrderLength;
}

void ProgramParams::setDrawOrderLength(int drawOrderLength) {
    this->drawOrderLength = drawOrderLength;
}
