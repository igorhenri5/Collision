#include "GlError.hpp"

void GlError::checkGlError(){
    int error = glGetError();
    std::string message = "";
    switch(error){
        case GL_INVALID_ENUM:
            message = "Invalid enum";
            break;
        case GL_INVALID_VALUE:
            message = "Invalid value";
            break;
        case GL_INVALID_OPERATION:
            message = "Invalid operation";
            break;
        case GL_OUT_OF_MEMORY:
            message = "Out of memory";
    }
    if(error != GL_NO_ERROR){
        std::cout << message << std::endl;
    }
}

void GlError::checkShaderCompileError(int shader){
    int compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(compiled == 0){
        std::cout << "ERRO Shader Compilation"<< std::endl;
    }
}

void GlError::checkProgramLinkError(int program){
    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(linked == 0){
        std::cout << "ERRO Program Link"<< std::endl;
    }
}

void GlError::checkProgramValidity(int program){
    int validate;
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &validate);
    if(validate == 0){
        std::cout << "ERRO Program Validate"<< std::endl;
    }
}
