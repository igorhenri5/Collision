#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "drawable/IDrawable.hpp"
#include "Rect.hpp"
#include "VerticesFactory.hpp"

class Rectangle: IDrawable{
private:
    Rect *rect;
    Frame *frame;
public:
    Rectangle(Rect *rect,  Rect *screenRect, float alpha);
    virtual void draw();
    virtual void update();
    ~Rectangle();
};

#endif
