#include "GlUtil.hpp"
#include <iostream>

int GlUtil::loadShader(int type, std::string shaderCode){
    int shader = glCreateShader(type);
    const char *c_str = shaderCode.c_str();
    if(shader == 0)
        return 0;
    glShaderSource(shader, 1, &c_str, NULL);
    glCompileShader(shader);
    return shader;
}

int GlUtil::loadProgram(int vertexShader, int fragmentShader){
    int program;
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;
}

void GlUtil::draw(int program, ProgramParams *programParams){
    int mvpMatrixHandle, positionHandle;
    int vertexCoordinateAxisNumber = 3;

    DrawableBuffer *drawableBuffer =  programParams->getDrawableBuffer();
    float *mvpMatrix = programParams->getMvpMatrix();
    int verticesLength = drawableBuffer->getVerticesLength();
    int drawOrderLength = drawableBuffer->getDrawOrderLength();

    std::cout << "program: " << program << std::endl;
    glUseProgram(program);

    positionHandle = glGetAttribLocation(program, "a_position");
    // mvpMatrixHandle = glGetUniformLocation(program, "u_mvpMatrix");
    //
    // glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, mvpMatrix);
    //
    // std::cout << "vertice id: " << drawableBuffer->getVerticesId() << std::endl;
    std::cout << "drawOrder id: " << drawableBuffer->getDrawOrderId() << std::endl;
    // std::cout << "verticesLength: " << verticesLength << std::endl;
    // std::cout << "drawOrderLength: " << drawOrderLength << std::endl;

    glEnableVertexAttribArray(positionHandle);
    glBindBuffer(GL_ARRAY_BUFFER, drawableBuffer->getVerticesId());
    glVertexAttribPointer(positionHandle, vertexCoordinateAxisNumber, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawableBuffer->getDrawOrderId());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    GlError::checkGlError();
    GlError::checkProgramValidity(program);
}
