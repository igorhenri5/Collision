#include "ScreenBounds.hpp"

ScreenBounds::ScreenBounds(Rect* bounds){
	this->bounds = bounds;
}

bool ScreenBounds::checkScreenUp(Rect* rect){
	return (rect->getY() + rect->getHeight() + 1 > this->bounds->getY() + this->bounds->getHeight());
}

bool ScreenBounds::checkScreenDown(Rect* rect){
    return (rect->getY() - 1 < this->bounds->getY());
}

bool ScreenBounds::checkScreenRight(Rect* rect){
    return (rect->getX()+rect->getWidth() + 1 > this->bounds->getX() + this->bounds->getWidth());
}

bool ScreenBounds::checkScreenLeft(Rect* rect){
    return (rect->getX() - 1 < this->bounds->getY());
}

bool ScreenBounds::checkCollisionY(MyRectangle* rectangle){
	return (rectangle->getDisplacementY() == 1 && checkScreenUp(rectangle->getRect()) || rectangle->getDisplacementY() == -1 && checkScreenDown(rectangle->getRect()));
}

bool ScreenBounds::checkCollisionX(MyRectangle* rectangle){
	return (rectangle->getDisplacementX() == 1 && checkScreenRight(rectangle->getRect()) || rectangle->getDisplacementX() == -1 && checkScreenLeft(rectangle->getRect()));
}

void ScreenBounds::collidesScreenBounds(MyRectangle* rectangle){
	 if(this->checkCollisionY(rectangle)){
         rectangle->setDisplacementY(rectangle->getDisplacementY() * -1);
     }
	 if(this->checkCollisionX(rectangle)){
         rectangle->setDisplacementX(rectangle->getDisplacementX() * -1);
     }
}
