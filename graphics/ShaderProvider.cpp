#include "ShaderProvider.hpp"

std::string ShaderProvider::getVertexShader(){
    return "\nin vec3 a_position;\n"
                //"uniform mat4 u_mvpMatrix;\n"
                "void main() {\n"
                   "gl_Position = vec4(a_position, 1.0);\n"
                "}\n";
}

std::string ShaderProvider::getFragmentShader(){
    return "\nprecision mediump float;\n"
               "void main() {\n"
                    "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
               "};";
}
