#ifndef __FRAME__
#define __FRAME__

class Frame{
private:
    float *vertices;
    short *drawOrder;
    DrawableBuffer drawableBuffer;
public:
    Frame(float *vertices, drawOrde *drawOrder);
    float* getVertices();
    short* getDrawOrder();
    ~Frame();
};

#endif
