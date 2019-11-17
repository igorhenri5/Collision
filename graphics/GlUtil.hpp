#ifndef __GLUTIL__
#define __GLUTIL__

#include <string>
#include <GL/glew.h>
#include "ProgramParams.hpp"
#include "GlError.hpp"

class GlUtil{
public:
    static int loadShader(int type, std::string shaderCode);
    static int loadProgram(int vertexShader, int fragmentShader);
    static void draw(int program, ProgramParams *programParams);
};

#endif
