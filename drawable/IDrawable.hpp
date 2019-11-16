#ifndef __IDRAWABLE__
#define __IDRAWABLE__

class IDrawable{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~IDrawable(){}
};

#endif
