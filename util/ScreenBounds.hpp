#ifndef __SCREENBOUNDS__
#define __SCREENBOUNDS__

#include "Rect.hpp"
#include "../entities/Rectangle.hpp"

class ScreenBounds{
private:
	Rect* bounds;
	bool checkScreenUp(MyRectangle* rectangle);
	bool checkScreenDown(MyRectangle* rectangle);
	bool checkScreenRight(MyRectangle* rectangle);
	bool checkScreenLeft(MyRectangle* rectangle);
	bool checkCollisionX(MyRectangle* rectangle);
	bool checkCollisionY(MyRectangle* rectangle);
public:
	ScreenBounds(Rect* bounds);
	void HandleCollisionScreenBounds(MyRectangle* rectangle);
};

#endif
