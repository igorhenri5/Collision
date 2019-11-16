#include "ProgramFactory.hpp"

ProgramFactory::ProgramFactory(){

    this->program = -1;
    this->vertexShaderCode = ShaderProvider::getVertexShader();
    this->fragmentShaderCode = ShaderProvider::getFragmentShader();
}

int ProgramFactory::getProgram(){
    if (this->program == -1) {
        this->vertexShader = GlUtil::loadShader(GL_VERTEX_SHADER, vertexShaderCode);
        this->fragmentShader = GlUtil::loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
        this->program = GlUtil::loadProgram(this->vertexShader , this->fragmentShader);
    }
    return this->program;
}

void ProgramFactory::deleteProgram(){
    if(this->program == -1){
        glDetachShader(this->program, this->vertexShader);
        glDetachShader(this->program, this->fragmentShader);
        glDeleteShader(this->vertexShader);
        glDeleteShader(this->fragmentShader);
        glDeleteProgram(this->program);
        this->program = -1;
    }
}

ProgramFactory::~ProgramFactory(){
    this->deleteProgram();
}
