#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "../drawable/IDrawable.hpp"
#include "../animation/Frame.hpp"
#include "../util/Rect.hpp"
#include "../util/VerticesFactory.hpp"

class Rectangle: IDrawable{
private:
    Rect *rect;
    Frame *frame;
    int displacementX, displacementY;
public:
    Rectangle(Rect *rect,  Rect *screenRect, float alpha, int displacementX, int displacementY);
    virtual void draw();
    virtual void update();
    ~Rectangle();
};

#endif
