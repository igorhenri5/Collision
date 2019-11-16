#ifndef __PROGRAMPARAMS__
#define __PROGRAMPARAMS__

#include "DrawableBuffer.hpp"

class ProgramParams {
private:
    DrawableBuffer *drawableBuffer;
    int verticesLength, drawOrderLength;
    float *mvpMatrix; // model view projection opengl matrix
public:
    ProgramParams(DrawableBuffer *drawableBuffer, float *mvpMatrix);
    float* getMvpMatrix();
    void setMvpMatrix(float *mvpMatrix);
    DrawableBuffer* getDrawableBuffer();
    void setDrawableBuffer(DrawableBuffer *drawableBuffer);
};

#endif
