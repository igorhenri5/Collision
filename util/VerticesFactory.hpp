#ifndef __VERTICESFACTORY__
#define __VERTICESFACTORY__

#include "Rect.hpp"

class VerticesFactory{
private:
    static float pixelToGlCoordinate(int pixel, int screenSize);
public:
    static float* initVertices(int *length, Rect *frameRect, Rect *screenRect, float alpha);
    static short* initDrawOrder(int *length);
};

#endif
