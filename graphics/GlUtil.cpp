#include "GlUtil.hpp"

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
    int samplerHandle, mvpMatrixHandle, positionHandle;
    int vertexCoordinateAxisNumber = 3;

    DrawableBuffer *drawableBuffer =  programParams->getDrawableBuffer();
    float *mvpMatrix = programParams->getMvpMatrix();
    int verticesLength = drawableBuffer->getVerticesLength();
    int drawOrderLength = drawableBuffer->getDrawOrderLength();

    glUseProgram(program);

    samplerHandle = glGetUniformLocation(program, "u_sampler");
    mvpMatrixHandle = glGetUniformLocation(program, "u_mvpMatrix");
    positionHandle = glGetAttribLocation(program, "a_position");

    glUniformMatrix4fv(mvpMatrixHandle, 1, false, mvpMatrix);

    glBindBuffer(GL_ARRAY_BUFFER, drawableBuffer->getVerticesId());
    glVertexAttribPointer(positionHandle, vertexCoordinateAxisNumber,
            GL_FLOAT, false, verticesLength, 0);

    glEnableVertexAttribArray(positionHandle);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawableBuffer->getDrawOrderId());
    glDrawElements(GL_TRIANGLES, drawOrderLength, GL_UNSIGNED_SHORT, 0);
}
