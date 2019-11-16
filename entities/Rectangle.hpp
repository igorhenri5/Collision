#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "../drawable/IDrawable.hpp"
#include "../animation/Frame.hpp"
#include "../util/Rect.hpp"
#include "../util/VerticesFactory.hpp"
#include "../graphics/ProgramFactory.hpp"
#include "../graphics/ProgramParams.hpp"
#include "../util/MatrixM.hpp"

class Rectangle: public IDrawable{
private:
    Rect *rect;
    Frame *frame;
    int mvpWidth, mvpHeight, displacementX, displacementY;
    ProgramFactory *programFactory;
    ProgramParams *programParams;
    float *mvp;
public:
    Rectangle(Rect *rect,  Rect *screenRect, float alpha, int displacementX, int displacementY, ProgramFactory *programFactory);
    virtual void draw();
    virtual void update();
    ~Rectangle();
};

#endif
