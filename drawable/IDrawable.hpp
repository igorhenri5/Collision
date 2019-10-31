#ifndef __DRAWABLEBUFFER__
#define __DRAWABLEBUFFER__

class IDrawable{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
};

#endif
