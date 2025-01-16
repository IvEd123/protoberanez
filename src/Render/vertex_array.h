#pragma once

#include <memory>
#include <GL/glew.h>
#include <vector>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void setData(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW);
    void setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

private:
    class Impl;
    std::unique_ptr<Impl> m_d;

};
