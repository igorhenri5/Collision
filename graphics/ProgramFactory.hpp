#ifndef __PROGRAMFACTORY__
#define __PROGRAMFACTORY__

#include <string>
#include "GlUtil.hpp"
#include "ShaderProvider.hpp"

class ProgramFactory {

private:
    int program, vertexShader, fragmentShader;
    std::string vertexShaderCode, fragmentShaderCode;

public:
    ProgramFactory();
    int getProgram();
    void deleteProgram();
    ~ProgramFactory();

};

#endif
