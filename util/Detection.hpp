#ifndef __DETCT__
#define __DETCT__

#include "Rect.hpp"
#include "../entities/Rectangle.hpp"

class Detector{
private:
	static int checkScreenUp(Rect* rect);
	static int checkScreenDown(Rect* rect);
	static int checkScreenRight(Rect* rect);
	static int checkScreenLeft(Rect* rect);
public:
	static int screenWidth;
	static int screenHeight;
	static int* collidesScreenBounds(MyRectangle* rectangle);
};

#endif