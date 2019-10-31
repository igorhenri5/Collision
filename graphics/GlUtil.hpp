#ifndef __GLUTIL__
#define __GLUTIL__

#include <GL/gl.h>
#include "ProgramParams.hpp"

class GlUtil{
public:
    static int loadShader(int type, String shaderCode);
    static int loadProgram(int vertexShader, int fragmentShader);
    static void draw(int program, ProgramParams *programParams);
};

#endif
