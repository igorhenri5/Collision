#ifndef __PROGRAMPARAMS__
#define __PROGRAMPARAMS__

#include "DrawableBuffer.hpp"

class ProgramParams {
private:
    DrawableBuffer *drawableBuffer;
    int verticesLength, drawOrderLength;
    float *mvpMatrix; // model view projection opengl matrix
public:
    ProgramParams(DrawableBuffer *drawableBuffer, int verticesLength, int drawOrderLength, float *mvpMatrix);
    float* getMvpMatrix();
    void setMvpMatrix(float *mvpMatrix);
    DrawableBuffer* getDrawableBuffer();
    void setDrawableBuffer(DrawableBuffer *drawableBuffer);
    int getVerticesLength();
    void setVerticesLength(int verticesLength);
    int getDrawOrderLength();
    void setDrawOrderLength(int drawOrderLength);
};

#endif
