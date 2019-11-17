#include "Detection.hpp"

int Detector::checkScreenUp(Rect* rect){
	return (rect->getY()+rect->getHeight() + 1 > screenHeight);
}
int Detector::checkScreenDown(Rect* rect){
    return (rect->getY() - 1 < 0);
}
int Detector::checkScreenRight(Rect* rect){
    return (rect->getX()+rect->getWidth() + 1 > screenWidth);
}
int Detector::checkScreenLeft(Rect* rect){
    return (rect->getX() - 1 < 0);
}

int* Detector::collidesScreenBounds(MyRectangle* rectangle){
    /*	
    	Em ordem:
        Nordeste  
        Sudeste  
        Sudoeste 
        Noroeste 
        Norte    
        Leste    
        Sul      
        Oeste    
    */

    //flags para colisao, uma para cada eixo
    int* collided = new int[2];
        collided[0] = 0; // Colisão no eixo Y
        collided[1] = 0; // Colisão no eixo X

     if(rectangle->getDisplacementX() == 1 && rectangle->getDisplacementY() == 1){
		collided[0] = checkScreenUp(rectangle->getRect());
		collided[1] = checkScreenRight(rectangle->getRect());
     }else if(rectangle->getDisplacementX() == 1 && rectangle->getDisplacementY() ==-1){
     	collided[0] = checkScreenDown(rectangle->getRect());
        collided[1] = checkScreenRight(rectangle->getRect());
     }else if(rectangle->getDisplacementX() ==-1 && rectangle->getDisplacementY() ==-1){
     	collided[0] = checkScreenDown(rectangle->getRect());
        collided[1] = checkScreenLeft(rectangle->getRect());
     }else if(rectangle->getDisplacementX() ==-1 && rectangle->getDisplacementY() == 1){
     	collided[0] = checkScreenUp(rectangle->getRect());
        collided[1] = checkScreenLeft(rectangle->getRect());
     }else if(rectangle->getDisplacementX() == 0 && rectangle->getDisplacementY() == 1){
     	collided[0] = checkScreenUp(rectangle->getRect());
     }else if(rectangle->getDisplacementX() == 1 && rectangle->getDisplacementY() == 0){
     	collided[1] = checkScreenRight(rectangle->getRect());
     }else if(rectangle->getDisplacementX() == 0 && rectangle->getDisplacementY() ==-1){
     	collided[0] = checkScreenDown(rectangle->getRect());
     }else if(rectangle->getDisplacementX() ==-1 && rectangle->getDisplacementY() == 0){
     	collided[1] = checkScreenLeft(rectangle->getRect());
     }

    return collided;
}