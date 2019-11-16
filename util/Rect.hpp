#ifndef __RECT__
#define __RECT__

class Rect{
private:
    int x, y, width, height;
public:
    Rect(int x, int y, int width, int height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int setX(int x);
    int setY(int y);
};

#endif
