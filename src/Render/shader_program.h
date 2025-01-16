#pragma once
#include <memory>
#include <GL/glew.h>

class Shader;

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(const Shader& shader);
    void link();
    void use() const;
    GLuint getID() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_d;

};