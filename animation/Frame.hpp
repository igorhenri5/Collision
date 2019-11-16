#ifndef __FRAME__
#define __FRAME__

#include "../graphics/DrawableBuffer.hpp"

class Frame{
private:
    float *vertices;
    short *drawOrder;
    DrawableBuffer *drawableBuffer;
public:
    Frame(float *vertices, short *drawOrder);
    float* getVertices();
    short* getDrawOrder();
    DrawableBuffer* getDrawableBuffer();
    ~Frame();
};

#endif
