#include "ShaderProvider.hpp"

std::string ShaderProvider::getVertexShader(){
    return "\nin vec4 a_position;\n"
                "uniform mat4 u_mvpMatrix;\n"
                "void main() {\n"
                   "gl_Position = u_mvpMatrix * a_position;\n"
                "}\n";
}

std::string ShaderProvider::getFragmentShader(){
    return "\nprecision mediump float;\n"
               "void main() {\n"
                    "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
               "};";
}
