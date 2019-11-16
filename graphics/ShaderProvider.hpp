#ifndef __SHADERPROVIDER__
#define __SHADERPROVIDER__

#include <string>

class ShaderProvider{
public:
    static std::string getVertexShader();
    static std::string getFragmentShader();
};

#endif
