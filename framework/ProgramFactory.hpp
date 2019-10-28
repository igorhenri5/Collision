#ifndef __PROGRAMFACTORY__
#define __PROGRAMFACTORY__

#include "GlUtil.hpp"
#include "ShaderProvider.hpp"

class ProgramFactory {

private:
    int program, vertexShader, fragmentShader;
    const char* vertexShaderCode, fragmentShaderCode;

public:
    ProgramFactory();
    int getProgram();
    void deleteProgram();
    ~ProgramFactory();

};

#endif
