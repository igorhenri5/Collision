#include <iostream>
#include <GL/freeglut.h>

void draw(){
    glClear (GL_COLOR_BUFFER_BIT);
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

void initOpenGLEnvironment(int weight, int height){
    glClearColor (0.0, 0.0, 0.0, 0.0); //black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, weight, 0.0, height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv){
    int weight, height;
    weight = 512;
    height = 512;
    std::cout << "UHAAAAA" << std::endl;
    initOpenGLEnvironment(weight, height);
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
