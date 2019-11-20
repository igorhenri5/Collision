#ifndef __MYRECTANG__
#define __MYRECTANG__

#include <pthread.h>
#include "../drawable/IDrawable.hpp"
#include "../util/Rect.hpp"

class MyRectangle: public IDrawable{
private:
    Rect *rect, *screenRect;
    int mvpWidth, mvpHeight, displacementX, displacementY;
//    pthread_mutex_t mutex;
    int collidedFlag;
public:
    MyRectangle(Rect *rect,  Rect *screenRect, int displacementX, int displacementY);
    Rect* getRect();
    void setRect(Rect*);
    int getDisplacementX();
    void setDisplacementX(int);
    int getDisplacementY();
    void setDisplacementY(int);
    int getCollidedFlag();
    void setCollidedFlag(int);
    //pthread_mutex_t* getMutex();
    void handleCollision(MyRectangle *renctangle);
    virtual void draw();
    virtual void update();
    ~MyRectangle();
};

#endif
