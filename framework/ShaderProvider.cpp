#include "ShaderProvider.hpp"

const char* ShaderProvider::getVertexShader(){
    return "\nattribute vec4 a_position;\n attribute vec2 a_textureCoord;\n"
                "uniform mat4 u_mvpMatrix;\n"
                "varying vec2 v_textureCoord;\n"
                "void main() {\n"
                   "gl_Position = u_mvpMatrix * a_position;\n"
                   "v_textureCoord= a_textureCoord;\n"
                "}\n";
}

const char* ShaderProvider::getFragmentShader(){
    return "\nprecision mediump float;\n"
               "void main() {\n"
                    "gl_FragColor = vec4(1.0, 0.0, 1.0, 0.0);\n"
               "};";
}
