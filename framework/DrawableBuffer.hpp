#ifndef __DRAWABLEBUFFER__
#define __DRAWABLEBUFFER__

#include <GL/gl.h>

class DrawableBuffer {
private:
    int length;
    int *drawableBuffers; //Array that optimizes the access of class buffers
public:
    DrawableBuffer(float *vertices, int verticeLength, short *drawOrder, int drawOrderLength);
    int getVerticesId();
    int getDrawOrderId();
    ~DrawableBuffer();
};

#endif
