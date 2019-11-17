#include "drawable/IDrawable.hpp"
#include "util/Rect.hpp"
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

namespace game{
    Rect *screenRect;
    std::vector<IDrawable *> drawables;
    ProgramFactory programFactory;
    QuadTree* quadtree;
}

void initDrawables(){

    game::quadtree = new QuadTree(0, new Rect(0,0,512,512));

    MyRectangle *rectangle;
    Rect *rect;
    rect = new Rect(64, 64, 64, 64);
    rectangle = new MyRectangle(rect, game::screenRect, 0, 1, 1, &(game::programFactory));
    game::drawables.push_back(rectangle);
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
    sleep(millis);
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
    int width, height;
    width = 512;
    height = 512;

    game::screenRect = new Rect(0, 0, width, height);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Programacao Paralela - TP");
    glewInit();
    initOpenGLEnvironment(width, height);
    initDrawables();
    glutDisplayFunc(draw);
    glutIdleFunc(mainloop);
    glutCloseFunc(onClose);
    glutKeyboardFunc(onKeyboardDownEvent);
    glutMainLoop();
    return 0;
}
