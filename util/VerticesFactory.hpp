#ifndef __VERTICESFACTORY__
#define __VERTICESFACTORY__

#include "Rect.hpp"
#include <GL/glew.h>

class VerticesFactory{
private:
    static GLfloat pixelToGlCoordinate(int pixel, int screenSize);
public:
    static GLfloat* initVertices(int *length, Rect *frameRect, Rect *screenRect, float alpha);
    static GLuint* initDrawOrder(int *length);
};

#endif
