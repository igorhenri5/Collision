#ifndef __MYRECTANG__
#define __MYRECTANG__

#include <GL/glew.h>
#include "../drawable/IDrawable.hpp"
#include "../animation/Frame.hpp"
#include "../util/Rect.hpp"
#include "../util/VerticesFactory.hpp"
#include "../graphics/ProgramFactory.hpp"
#include "../graphics/ProgramParams.hpp"
#include "../util/MatrixM.hpp"

class MyRectangle: public IDrawable{
private:
    Rect *rect, *screenRect;
    Frame *frame;
    int mvpWidth, mvpHeight, displacementX, displacementY;
    ProgramFactory *programFactory;
    ProgramParams *programParams;
    float *mvpMatrix;
public:
    MyRectangle(Rect *rect,  Rect *screenRect, float alpha, int displacementX, int displacementY, ProgramFactory *programFactory);
    Rect* getRect();
    void setRect(Rect*);
    Frame* getFrame();
    void setFrame(Frame*);
    int getDisplacementX();
    void setDisplacementX(int);
    int getDisplacementY();
    void setDisplacementY(int);
    void collisionCheck(MyRectangle *renctangle);
    virtual void draw();
    virtual void update();
    ~MyRectangle();
};

#endif
