#include "drawable/IDrawable.hpp"
#include "util/Rect.hpp"
#include "util/Detection.hpp"
#include "entities/Rectangle.hpp"
#include "graphics/ProgramFactory.hpp"
#include "quadtree/QuadTree.hpp"
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <sys/time.h>
#include <GL/freeglut.h>
#include <string.h>
#include <cstdlib>


#define  RECSIZE  8

#ifdef _WIN32
    #include <windows.h>
    void sleep(unsigned milliseconds){
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    void sleep(unsigned milliseconds){
        usleep(milliseconds);
    }
#endif

struct timeval tempoInicial, tempoFinal;
float elapsedTime;
char buffer[64];

int Detector::screenWidth = 512;
int Detector::screenHeight = 512;

namespace game{
    Rect *screenRect;
    std::vector<IDrawable *> drawables;
    ProgramFactory programFactory;
    QuadTree* quadtree;
    int width;
    int height;
    int seed = 420;
}

void initDrawables(){

    game::quadtree = new QuadTree(0, new Rect(0,0,512,512));

 /*   
    MyRectangle *rectangle;
    Rect *rect;
    rect = new Rect(64, 64, 64, 64);
    rectangle = new MyRectangle(rect, game::screenRect, 0, 1, 1, &(game::programFactory));
    game::drawables.push_back(rectangle);
*/
    game::drawables.push_back(new MyRectangle(new Rect(32, 192, RECSIZE, RECSIZE), game::screenRect,  0, -1, -1, &(game::programFactory)));
    game::drawables.push_back(new MyRectangle(new Rect(64, 64, RECSIZE, RECSIZE), game::screenRect,   0,  0, -1, &(game::programFactory)));
    game::drawables.push_back(new MyRectangle(new Rect(128, 128, RECSIZE, RECSIZE), game::screenRect, 0,  1,  1, &(game::programFactory)));
    game::drawables.push_back(new MyRectangle(new Rect(192, 128, RECSIZE, RECSIZE), game::screenRect, 0,  1,  0, &(game::programFactory)));

 /*
    srand(game::seed); 
    int displacementX,displacementY;
    for(int i=0; i<game::height; i+=16){
        displacementX = (rand()%2)-1;
        displacementY = (rand()%2)-1;

        displacementX = 1;
        displacementY = 0;

        game::drawables.push_back(new MyRectangle(new Rect(0, i, RECSIZE, RECSIZE), game::screenRect, 0, displacementX, displacementY, &(game::programFactory)));
    }
*/
}

void update(){
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        (*drawable)->update();
    }
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // std::cout << "draw" << std::endl;
    // std::cout << game::drawables.size() << std::endl;
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        (*drawable)->draw();
    }
    glutSwapBuffers();
}

void mainloop(){
    gettimeofday(&tempoInicial, NULL);
    update();
    draw();
    gettimeofday(&tempoFinal, NULL);
    elapsedTime = ((tempoFinal.tv_sec  - tempoInicial.tv_sec) * 1000000u + tempoFinal.tv_usec - tempoInicial.tv_usec) / 1.e6;
    snprintf(buffer, sizeof(buffer), "%f", elapsedTime);
    glutSetWindowTitle(buffer);
    float millis, fps;
    fps = 30;
    // std::cout << 1000.0f / 30 << std::endl;
    // std::cout << "elapsedTime (millis): " << elapsedTime * 1000.0f << std::endl;
    millis = 1000.0f / fps - elapsedTime * 1000.0f;
    if(millis < 0){
        std::cout << "Lag (millis): " << millis << std::endl;
        millis = 0;
    }
    //sleep(millis);
    //desliguei o sync pra ver a diferença nos dos monitores
}

void onKeyboardDownEvent(unsigned char key, int x, int y){
    std::cout << "onKeyboardDownEvent" << std::endl;
}

void onClose(){
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        delete (*drawable);
    }
    delete game::screenRect;
    std::cout << "onClose" << std::endl;
}

void initOpenGLEnvironment(int width, int height){
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background frame color
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv){
    game::width = 512;
    game::height = 512;

    game::screenRect = new Rect(0, 0, game::width, game::height);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(game::width, game::height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Programacao Paralela - TP");
    glewInit();
    initOpenGLEnvironment(game::width, game::height);
    initDrawables();
    glutDisplayFunc(draw);
    glutIdleFunc(mainloop);
    glutCloseFunc(onClose);
    glutKeyboardFunc(onKeyboardDownEvent);
    glutMainLoop();
    return 0;
}
