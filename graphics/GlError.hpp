#ifndef __GLERROR__
#define __GLERROR__

#include <GL/glew.h>
#include <string>
#include <iostream>

class GlError{
public:
    static void checkGlError();
    static void checkShaderCompileError(int shader);
    static void checkProgramLinkError(int program);
    static void checkProgramValidity(int program);
};

#endif
