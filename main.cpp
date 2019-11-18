#include "drawable/IDrawable.hpp"
#include "util/Rect.hpp"
#include "util/ScreenBounds.hpp"
#include "entities/Rectangle.hpp"
#include "graphics/ProgramFactory.hpp"
#include "quadtree/QuadTree.hpp"
#include "threadpool/ThreadPool.hpp"
#include "threadpool/MasterFlag.hpp"
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <sys/time.h>
#include <GL/freeglut.h>
#include <string.h>
#include <cstdlib>

#define  RECSIZE  4

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

struct timeval tempoInicialAll, tempoFinalAll;
struct timeval tempoInicial, tempoFinal;
float elapsedTime;
char buffer[64];

namespace game{
    Rect *screenRect;
    ScreenBounds *screenBounds;
    std::vector<IDrawable *> drawables;
    ProgramFactory programFactory;
    QuadTree* quadtree;
    int seed = 420;
    ThreadPool *threadPool;
    MasterFlag *masterFlag;
}

void printElapsedTime(){
    snprintf(buffer, sizeof(buffer), "%f", elapsedTime);
    glutSetWindowTitle(buffer);
    std::cout << "elapsedTime: " << elapsedTime << std::endl;
}

int x = 100;

float getSeconds(struct timeval *tempoI, struct timeval *tempoF){
    return ((tempoF->tv_sec  - tempoI->tv_sec) * 1000000u + tempoF->tv_usec - tempoI->tv_usec) / 1.e6;
}


void forceSync(float fps){
    float millis;
    millis = 1000.0f / fps - elapsedTime * 1000.0f;
    if(millis < 0){
        std::cout << "Lag (millis): " << millis << std::endl;
        millis = 0.0f;
    }
    sleep(millis);
}

void initDrawables(){
    srand(game::seed);
    int displacementX, displacementY;
    for(int i=0; i < game::screenRect->getWidth(); i += 16){
        for(int j = 0; j < game::screenRect->getHeight(); j += 64){
            displacementX = (rand() % 3) - 1;
            displacementY = (rand() % 3) - 1;

            game::drawables.push_back(new MyRectangle(new Rect(i, j, RECSIZE, RECSIZE), game::screenRect, 0, displacementX, displacementY, &(game::programFactory)));
        }
    }
    std::cout << "numero de elementos: " << game::drawables.size() << std::endl;
}

void worstCollision(){
    MyRectangle *rectangle;
    for(int i = 0; i < game::drawables.size(); i++){
        for(int j = i + 1; j < game::drawables.size(); j++){
            rectangle = (MyRectangle *) game::drawables.at(i);
            rectangle->collides((MyRectangle *) game::drawables.at(j));
        }
    }
}

void parralelCollision(){
    Task *task;
    int inicioParticao, fimParticao, numParticoes, tamanhoParticao;

    tamanhoParticao = (game::drawables.size() + game::threadPool->size - 1) / game::threadPool->size;

    if(tamanhoParticao < 100) // tamanho minimo particao
        tamanhoParticao = 100;

    numParticoes = (game::drawables.size() + tamanhoParticao - 1) / tamanhoParticao;
    game::masterFlag->reset(numParticoes);

    for(long int i = 0; i < numParticoes; i++){
        inicioParticao = i * tamanhoParticao;
        fimParticao = inicioParticao + tamanhoParticao;
        if(fimParticao > game::drawables.size()){
          fimParticao = game::drawables.size();
        }
        game::threadPool->addTask(new AddTask(game::masterFlag, game::quadtree, game::drawables.begin() + inicioParticao, game::drawables.begin() + fimParticao));
    }
    game::masterFlag->wait();
}

void update(){
    game::quadtree->clear();

    gettimeofday(&tempoInicial, NULL);
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        game::quadtree->add((MyRectangle *)(*drawable));
    }
    gettimeofday(&tempoFinal, NULL);
    elapsedTime = getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Add ";
        printElapsedTime();
    }

    gettimeofday(&tempoInicial, NULL);

    game::quadtree->collidesAll();

    gettimeofday(&tempoFinal, NULL);
    elapsedTime = getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Cld ";
        printElapsedTime();
    }

    gettimeofday(&tempoInicial, NULL);
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        game::screenBounds->collidesScreenBounds((MyRectangle *)(*drawable));
        (*drawable)->update();
    }
    gettimeofday(&tempoFinal, NULL);
    elapsedTime = getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Upt ";
        printElapsedTime();
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
    gettimeofday(&tempoInicialAll, NULL);
    update();
    gettimeofday(&tempoFinalAll, NULL);
    draw();

    elapsedTime = getSeconds(&tempoInicialAll, &tempoFinalAll);
    if(x<=0){
        std::cout << "All ";
        printElapsedTime();
        x=100;
    }
    x--;
}

void onKeyboardDownEvent(unsigned char key, int x, int y){
    std::cout << "onKeyboardDownEvent" << std::endl;
}

void onClose(){
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        delete (*drawable);
    }
    delete game::screenRect;
    delete game::screenBounds;
    delete game::quadtree;
    delete game::threadPool;
    delete game::masterFlag;
    std::cout << "onClose" << std::endl;
}

void initOpenGLEnvironment(int width, int height){
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background frame color
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv){
    game::screenRect = new Rect(0, 0, 1280, 720);
    game::screenBounds = new ScreenBounds(game::screenRect);
    game::quadtree = new QuadTree(0, new Rect(0, 0, game::screenRect->getWidth(), game::screenRect->getHeight()));
    game::threadPool = new ThreadPool(4);
    game::masterFlag = new MasterFlag(0);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(game::screenRect->getWidth(), game::screenRect->getHeight());
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Programacao Paralela - TP");
    glewInit();
    initOpenGLEnvironment(game::screenRect->getWidth(), game::screenRect->getHeight());
    initDrawables();
    glutDisplayFunc(draw);
    glutIdleFunc(mainloop);
    glutCloseFunc(onClose);
    glutKeyboardFunc(onKeyboardDownEvent);
    glutMainLoop();
    return 0;
}
