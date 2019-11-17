#ifndef __DRAWABLEBUFFER__
#define __DRAWABLEBUFFER__

#include <GL/glew.h>

class DrawableBuffer {
private:
    int length, verticesLength, drawOrderLength;
    GLuint *buffers; //Array that optimizes the access of class buffers
public:
    DrawableBuffer(GLfloat *vertices, int verticesLength, GLuint *drawOrder, int drawOrderLength);
    unsigned int getVerticesId();
    unsigned int getDrawOrderId();
    int getVerticesLength();
    int getDrawOrderLength();
    ~DrawableBuffer();
};

#endif
