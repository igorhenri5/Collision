#ifndef __FRAME__
#define __FRAME__

#include "../graphics/DrawableBuffer.hpp"
#include <GL/glew.h>

class Frame{
private:
    GLfloat *vertices;
    GLuint *drawOrder;
    DrawableBuffer *drawableBuffer;
public:
    Frame(GLfloat *vertices, int verticeLength, GLuint *drawOrder, int drawOrderLength);
    GLfloat* getVertices();
    GLuint* getDrawOrder();
    DrawableBuffer* getDrawableBuffer();
    ~Frame();
};

#endif
