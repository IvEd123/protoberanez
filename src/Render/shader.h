#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>

class Shader {
public:
    enum Type {
        VertexShader = 0,
        FragmentShader
    };
    
    Shader(Shader::Type type, const std::string& source);
    ~Shader();


    GLuint getID() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_d;

};  