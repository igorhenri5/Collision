#include "ShaderProvider.hpp"

const char* ShaderProvider::getVertexShader(){
    return "\nattribute vec4 a_position;\n"
                "uniform mat4 u_mvpMatrix;\n"
                "void main() {\n"
                   "gl_Position = u_mvpMatrix * a_position;\n"
                "}\n";
}

const char* ShaderProvider::getFragmentShader(){
    return "\nprecision mediump float;\n"
               "void main() {\n"
                    "gl_FragColor = vec4(1.0, 0.0, 1.0, 0.0);\n"
               "};";
}
