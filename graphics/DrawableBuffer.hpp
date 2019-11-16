#ifndef __DRAWABLEBUFFER__
#define __DRAWABLEBUFFER__

#include <GL/glew.h>

class DrawableBuffer {
private:
    int length;
    GLuint *drawableBuffers; //Array that optimizes the access of class buffers
public:
    DrawableBuffer(GLfloat *vertices, int verticeLength, GLshort *drawOrder, int drawOrderLength);
    int getVerticesId();
    int getDrawOrderId();
    ~DrawableBuffer();
};

#endif
