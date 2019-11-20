#include "drawable/IDrawable.hpp"
#include "util/Rect.hpp"
#include "util/ScreenBounds.hpp"
#include "entities/Rectangle.hpp"
#include "graphics/ProgramFactory.hpp"
#include "quadtree/QuadTree.hpp"
#include "threadpool/ThreadPool.hpp"
#include "threadpool/MasterFlag.hpp"
#include "threadpool/AddTask.hpp"
#include "threadpool/MountTask.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <time.h>
#include <chrono>
#include <sys/time.h>
#include <GL/freeglut.h>
#include <string>
#include <cstdlib>
#include <iomanip>

#define  RECSIZE  4

struct timeval tempoInicialAll, tempoFinalAll;
struct timeval tempoInicial, tempoFinal;
float elapsedTimeAdd, elapsedTimeMount, elapsedTimeUpt, elapsedTimeCld, elapsedTimeCln, elapsedTimeAll;
char buffer[64];
int x = 100;

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

void printElapsedTime(float elapsedTime){
    snprintf(buffer, sizeof(buffer), "%f", elapsedTime);
    glutSetWindowTitle(buffer);
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << "elapsedTime: " << elapsedTime << std::endl;
}

float getSeconds(struct timeval *tempoI, struct timeval *tempoF){
    return ((tempoF->tv_sec  - tempoI->tv_sec) * 1000000u + tempoF->tv_usec - tempoI->tv_usec) / 1.e6;
}

void initDrawables(){
    srand(game::seed);
    int displacementX, displacementY;
    int iInc = RECSIZE*RECSIZE;
    int jInc = iInc;
    for(int i=0; i < game::screenRect->getWidth(); i += iInc){
        for(int j = 0; j < game::screenRect->getHeight(); j += jInc){
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
            rectangle->handleCollision((MyRectangle *) game::drawables.at(j));
        }
    }
}

void addSerial(){
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        game::quadtree->add((MyRectangle *)(*drawable));
    }
}

void addParallel(){
    int inicioParticao, fimParticao, numParticoes, tamanhoParticao;

    tamanhoParticao = (game::drawables.size() + game::threadPool->size - 1) / game::threadPool->size;

    if(tamanhoParticao < 100) // tamanho minimo particao
        tamanhoParticao = 100;

    numParticoes = (game::drawables.size() + tamanhoParticao - 1) / tamanhoParticao;

    game::masterFlag->reset(numParticoes);
    for(int i = 0; i < numParticoes; i++){
        inicioParticao = i * tamanhoParticao;
        fimParticao = inicioParticao + tamanhoParticao;
        if(fimParticao > game::drawables.size()){
          fimParticao = game::drawables.size();
        }
        game::threadPool->addTask(new AddTask(game::masterFlag, game::quadtree, game::drawables.begin() + inicioParticao, game::drawables.begin() + fimParticao));
    }
    game::masterFlag->wait();
}

std::vector<std::vector<std::pair<MyRectangle*, MyRectangle*>>*>* mountPairLists(){
    std::vector<std::vector<std::pair<MyRectangle*, MyRectangle*>>*> *pairLists;

    pairLists = new std::vector<std::vector<std::pair<MyRectangle*, MyRectangle*>>*>();

    game::masterFlag->reset(game::threadPool->size);
    for(int i = 0; i < game::threadPool->size; i++){
        pairLists->push_back(new std::vector<std::pair<MyRectangle*, MyRectangle*>>());
        game::threadPool->addTask(new MountTask(game::masterFlag, game::quadtree, i, game::threadPool->size, pairLists->at(i)));
    }
    game::masterFlag->wait();
    return pairLists;
}


void parallelHandleAllCollisions(){
    std::vector<std::vector<std::pair<MyRectangle*, MyRectangle*>>*> *pairLists;
    gettimeofday(&tempoInicial, NULL);
    pairLists = mountPairLists();
    gettimeofday(&tempoFinal, NULL);
    elapsedTimeMount += getSeconds(&tempoInicial, &tempoFinal);

    if(x<=0){
        std::cout << "Mnt ";
        printElapsedTime(elapsedTimeMount / 100);
        elapsedTimeMount = 0;
    }
    game::masterFlag->reset(pairLists->size());
    for(int i = 0; i < pairLists->size(); i++){
        game::threadPool->addTask(new HandleCollisionTask(game::masterFlag, pairLists->at(i)->begin(), pairLists->at(i)->end()));
    }
    game::masterFlag->wait();

    for (auto pairList = pairLists->begin(); pairList != pairLists->end(); ++pairList){
        delete *pairList;
    }
    delete pairLists;
}

//da pra paralelizar isso aqui
void cleanFlags(){
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        ((MyRectangle *)(*drawable))->setCollidedFlag(0);
    }
}

void update(){
    game::quadtree->clear();

    gettimeofday(&tempoInicial, NULL);
    //Adicionar
    // addSerial();
    addParallel();
    gettimeofday(&tempoFinal, NULL);
    elapsedTimeAdd += getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Add ";
        printElapsedTime(elapsedTimeAdd / 100);
        elapsedTimeAdd = 0;
    }

    gettimeofday(&tempoInicial, NULL);

    // game::quadtree->handleAllCollisions();
    parallelHandleAllCollisions();

    gettimeofday(&tempoFinal, NULL);
    elapsedTimeCld += getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Cld ";
        printElapsedTime(elapsedTimeCld / 100);
        elapsedTimeCld = 0;
    }

    gettimeofday(&tempoInicial, NULL);
    for (auto drawable = game::drawables.begin(); drawable != game::drawables.end(); ++drawable){
        game::screenBounds->handleCollisionScreenBounds((MyRectangle *)(*drawable));
        // std::cout << "update" << std::endl;
        (*drawable)->update();
    }
    gettimeofday(&tempoFinal, NULL);
    elapsedTimeUpt += getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Upt ";
        printElapsedTime(elapsedTimeUpt / 100);
        elapsedTimeUpt = 0;
    }

    gettimeofday(&tempoInicial, NULL);
    //Limpar
    cleanFlags();
    gettimeofday(&tempoFinal, NULL);
    elapsedTimeCln += getSeconds(&tempoInicial, &tempoFinal);
    if(x<=0){
        std::cout << "Cln ";
        printElapsedTime(elapsedTimeCln / 100);
        elapsedTimeCln = 0;
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

    elapsedTimeAll += getSeconds(&tempoInicialAll, &tempoFinalAll);
    if(x<=0){
        std::cout << "All ";
        printElapsedTime(elapsedTimeAll / 100);
        std::cout << std::endl;
        elapsedTimeAll = 0;
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
    int threadNum = 4;

    if(argc == 2){
        std::string param1(argv[1]);
        game::screenRect = new Rect(0, 0, std::stoi(param1), std::stoi(param1));
    }
    else if(argc == 3){
        std::string param1(argv[1]);
        std::string param2(argv[2]);
        game::screenRect = new Rect(0, 0, std::stoi(param1), std::stoi(param2));
    }else if(argc == 4){
        std::string param1(argv[1]);
        std::string param2(argv[2]);
        std::string param3(argv[3]);
        game::screenRect = new Rect(0, 0, std::stoi(param1), std::stoi(param2));
        threadNum = std::stoi(param3);
    }else{
        game::screenRect = new Rect(0, 0, 1280, 720);
    }

    game::screenBounds = new ScreenBounds(game::screenRect);
    game::quadtree = new QuadTree(0, new Rect(0, 0, game::screenRect->getWidth(), game::screenRect->getHeight()));
    game::threadPool = new ThreadPool(threadNum);
    game::masterFlag = new MasterFlag(0);
    elapsedTimeAdd = 0;
    elapsedTimeUpt = 0;
    elapsedTimeCld = 0;
    elapsedTimeAll = 0;


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //Sem Vsync
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
