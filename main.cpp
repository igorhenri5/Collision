#include <iostream>
#include <GL/freeglut.h>

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void mainloop(){
    draw();
}

void onClose(){
    std::cout << "onClose" << std::endl;
}

void onKeyboardDownEvent(unsigned char key, int x, int y){
    std::cout << "onKeyboardDownEvent" << std::endl;
}

void initOpenGLEnvironment(){
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background frame color
}

int main(int argc, char **argv){
    int weight, height;
    weight = 512;
    height = 512;
    initOpenGLEnvironment();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(weight, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Programacao Paralela - TP");
    glutDisplayFunc(draw);
    glutIdleFunc(mainloop);
    glutCloseFunc(onClose);
    glutKeyboardFunc(onKeyboardDownEvent);
    glutMainLoop();
    return 0;
}
