#ifndef __DRAWABLEBUFFER__
#define __DRAWABLEBUFFER__

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

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
