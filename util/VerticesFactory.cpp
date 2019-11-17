#include "VerticesFactory.hpp"

GLfloat VerticesFactory::pixelToGlCoordinate(int pixel, int screenSize){
    return pixel * (2.0f / screenSize) - 1.0;
}

GLfloat VerticesFactory::pixelToGlCoordinateVariation(int pixel, int screenSize){
    return pixel * (2.0f / screenSize);
}

GLfloat* VerticesFactory::initVertices(int *length, Rect *frameRect, Rect *screenRect, float alpha){
    GLfloat *vertices = new GLfloat[12];
    vertices[0] = pixelToGlCoordinate(0, screenRect->getWidth());
    vertices[1] = pixelToGlCoordinate(frameRect->getHeight(), screenRect->getHeight());
    vertices[2] = alpha;
    //set bottom left vertex
    vertices[3] = pixelToGlCoordinate(0, screenRect->getWidth());
    vertices[4] = pixelToGlCoordinate(0, screenRect->getHeight());
    vertices[5] = alpha;
    //set bottom right vertex
    vertices[6] = pixelToGlCoordinate(frameRect->getWidth(), screenRect->getWidth());
    vertices[7] = pixelToGlCoordinate(0, screenRect->getHeight());
    vertices[8] = alpha;
    //set top right vertex
    vertices[9] = pixelToGlCoordinate(frameRect->getWidth(), screenRect->getWidth());
    vertices[10] = pixelToGlCoordinate(frameRect->getHeight(), screenRect->getHeight());
    vertices[11] = alpha;

    *length = 12;
    return vertices;
}

GLuint* VerticesFactory::initDrawOrder(int *length){
    GLuint *drawOrder = new GLuint[6];
    drawOrder[0] = 0;
    drawOrder[1] = 1;
    drawOrder[2] = 2;
    drawOrder[3] = 0;
    drawOrder[4] = 2;
    drawOrder[5] = 3;
    *length = 6;
    return drawOrder;
}
