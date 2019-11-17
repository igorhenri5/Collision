#ifndef __SCREENBOUNDS__
#define __SCREENBOUNDS__

#include "Rect.hpp"
#include "../entities/Rectangle.hpp"

class ScreenBounds{
private:
	Rect* bounds;
	bool checkScreenUp(Rect* rect);
	bool checkScreenDown(Rect* rect);
	bool checkScreenRight(Rect* rect);
	bool checkScreenLeft(Rect* rect);
	bool checkCollisionX(MyRectangle* rectangle);
	bool checkCollisionY(MyRectangle* rectangle);
public:
	ScreenBounds(Rect* bounds);
	void collidesScreenBounds(MyRectangle* rectangle);
};

#endif
