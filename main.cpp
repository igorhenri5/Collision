#include "drawable/IDrawable.hpp"
#include "util/Rect.hpp"
#include "entities/Rectangle.hpp"
#include "graphics/ProgramFactory.hpp"
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
    ProgramFactory programFacory;
}

void update(){
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        (*drawable)->update();
    }
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    std::cout << elapsedTime << std::endl;
    //sleep(1000/60);
    sleep(8);
}

void onKeyboardDownEvent(unsigned char key, int x, int y){
    std::cout << "onKeyboardDownEvent" << std::endl;
}

void init(int width, int height){
    myRectangle *rectangle;
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Programacao Paralela - TP");
    initOpenGLEnvironment(width, height);
    glutDisplayFunc(draw);
    glutIdleFunc(mainloop);
    glutCloseFunc(onClose);
    glutKeyboardFunc(onKeyboardDownEvent);
    glutMainLoop();
    return 0;
}
