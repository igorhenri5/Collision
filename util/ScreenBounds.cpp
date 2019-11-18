#include "ScreenBounds.hpp"

ScreenBounds::ScreenBounds(Rect* bounds){
	this->bounds = bounds;
}

bool ScreenBounds::checkScreenUp(MyRectangle* rectangle){
	return (rectangle->getRect()->getY() + rectangle->getRect()->getHeight() + rectangle->getDisplacementY() > this->bounds->getY() + this->bounds->getHeight());
}

bool ScreenBounds::checkScreenDown(MyRectangle* rectangle){
    return (rectangle->getRect()->getY() + rectangle->getDisplacementY() < this->bounds->getY());
}

bool ScreenBounds::checkScreenRight(MyRectangle* rectangle){
    return (rectangle->getRect()->getX() + rectangle->getRect()->getWidth() + rectangle->getDisplacementX() > this->bounds->getX() + this->bounds->getWidth());
}

bool ScreenBounds::checkScreenLeft(MyRectangle* rectangle){
    return (rectangle->getRect()->getX() + rectangle->getDisplacementX() < this->bounds->getY());
}

bool ScreenBounds::checkCollisionY(MyRectangle* rectangle){
	return (rectangle->getDisplacementY() > 0 && checkScreenUp(rectangle) || rectangle->getDisplacementY() < 0 && checkScreenDown(rectangle));
}

bool ScreenBounds::checkCollisionX(MyRectangle* rectangle){
	return (rectangle->getDisplacementX() > 0 && checkScreenRight(rectangle) || rectangle->getDisplacementX() < 0 && checkScreenLeft(rectangle));
}

void ScreenBounds::handleCollisionScreenBounds(MyRectangle* rectangle){
	 if(this->checkCollisionY(rectangle)){
         rectangle->setDisplacementY(rectangle->getDisplacementY() * -1);
     }
	 if(this->checkCollisionX(rectangle)){
         rectangle->setDisplacementX(rectangle->getDisplacementX() * -1);
     }
}
