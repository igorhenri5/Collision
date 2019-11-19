#include "Rectangle.hpp"

MyRectangle::MyRectangle(Rect *rect, Rect *screenRect, float alpha, int displacementX, int displacementY, ProgramFactory *programFactory){
    int vertcesLegth, drawOrderLength;
    GLfloat *vertices;
    GLuint *drawOrder;

    this->rect = rect;
    this->screenRect = screenRect;

    //init Frame
    vertices = VerticesFactory::initVertices(&vertcesLegth, rect, screenRect, alpha);
    drawOrder = VerticesFactory::initDrawOrder(&drawOrderLength);
    this->frame = new Frame(vertices, vertcesLegth, drawOrder, drawOrderLength);

    //init displacement
    this->displacementX = displacementX;
    this->displacementY = displacementY;

    //init mvpMatrix
    this->mvpWidth = 4;
    this->mvpHeight = 4;
    this->mvpMatrix = new float[this->mvpHeight * this->mvpWidth];
    MatrixM::identity(this->mvpMatrix, this->mvpWidth, this->mvpHeight);
    MatrixM::translate(this->mvpMatrix, this->mvpWidth, this->mvpHeight,
        VerticesFactory::pixelToGlCoordinateVariation(rect->getX(), screenRect->getWidth()),
        VerticesFactory::pixelToGlCoordinateVariation(rect->getY(), screenRect->getHeight()),
         0);

    this->programParams = new ProgramParams(this->frame->getDrawableBuffer(), this->mvpMatrix);

    this->programFactory = programFactory;

    //pthread_mutex_init(&this->mutex, 0);
    this->collidedFlag = 0;
}

Rect* MyRectangle::getRect(){
    return this->rect;
}
Frame* MyRectangle::getFrame(){
    return this->frame;
}

void MyRectangle::setRect(Rect* rect){
    this->rect = rect;
}

void MyRectangle::setFrame(Frame* frame){
    this->frame = frame;
}

int MyRectangle::getDisplacementX(){
    return this->displacementX;
}

void MyRectangle::setDisplacementX(int val){
    this->displacementX = val;
}

int MyRectangle::getDisplacementY(){
    return this->displacementY;
}

void MyRectangle::setDisplacementY(int val){
    this->displacementY = val;
}

int MyRectangle::getCollidedFlag(){
    return this->collidedFlag;
}

void MyRectangle::setCollidedFlag(int val){
    this->collidedFlag = val;
}
/*
pthread_mutex_t* MyRectangle::getMutex(){
    return &this->mutex;
}
*/
void MyRectangle::handleCollision(MyRectangle *rectangle){
    //if(!this->collidedFlag){
     
        //pthread_mutex_lock(&this->mutex);
        //pthread_mutex_lock(rectangle->getMutex());
        if(!this->collidedFlag){

            Rect rectA(
                this->rect->getX() + this->displacementX,
                this->rect->getY() + this->displacementY,
                this->rect->getWidth(),
                this->rect->getHeight()
            );
            Rect rectB(
                rectangle->getRect()->getX() + rectangle->getDisplacementX(),
                rectangle->getRect()->getY() + rectangle->getDisplacementY(),
                rectangle->getRect()->getWidth(),
                rectangle->getRect()->getHeight()
            );

            if(rectA.intersect(&rectB)){
                this->collidedFlag = 1;
                rectangle->setCollidedFlag(1);
            }
        }

        //pthread_mutex_unlock(rectangle->getMutex());
        //pthread_mutex_unlock(&this->mutex);
    //}
}

//se deu colisão = this->col

void MyRectangle::draw(){
    // std::cout << "draw rect" << std::endl;
    // std::cout << this->programFactory->getProgram() << std::endl;
    GlUtil::draw(programFactory->getProgram(), this->programParams);
}

void MyRectangle::update(){

    if(this->collidedFlag){
        this->displacementY *= -1;
        this->displacementX *= -1;
    }

    this->rect->setX(this->rect->getX() + this->displacementX);
    this->rect->setY(this->rect->getY() + this->displacementY);

    MatrixM::translate(this->mvpMatrix, this->mvpWidth, this->mvpHeight,
        VerticesFactory::pixelToGlCoordinateVariation(this->displacementX, this->screenRect->getWidth()),
        VerticesFactory::pixelToGlCoordinateVariation(this->displacementY, this->screenRect->getHeight()),
        0);

}

MyRectangle::~MyRectangle(){
    //pthread_mutex_destroy(&this->mutex);
    delete this->mvpMatrix;
    delete this->rect;
    delete this->frame;
    delete this->programParams;
}
