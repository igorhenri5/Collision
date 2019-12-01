#include "ProgramParams.hpp"

ProgramParams::ProgramParams(DrawableBuffer *drawableBuffer, float *mvpMatrix) {
    this->drawableBuffer = drawableBuffer;
    this->mvpMatrix = mvpMatrix;
}

float* ProgramParams::getMvpMatrix(){
    return this->mvpMatrix;
}

void ProgramParams::setMvpMatrix(float *mvpMatrix) {
    this->mvpMatrix = mvpMatrix;
}

DrawableBuffer* ProgramParams::getDrawableBuffer() {
    return this->drawableBuffer;
}

void ProgramParams::setDrawableBuffer(DrawableBuffer *drawableBuffer) {
    this->drawableBuffer = drawableBuffer;
}
