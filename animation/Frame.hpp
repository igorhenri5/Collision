#ifndef __FRAME__
#define __FRAME__

#include "../graphics/DrawableBuffer.hpp"

class Frame{
private:
    float *vertices;
    short *drawOrder;
    DrawableBuffer *drawableBuffer;
public:
    Frame(float *vertices, int verticeLength, short *drawOrder, int drawOrderLength);
    float* getVertices();
    short* getDrawOrder();
    DrawableBuffer* getDrawableBuffer();
    ~Frame();
};

#endif
