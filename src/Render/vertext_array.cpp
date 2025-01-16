#include "vertex_array.h"

class VertexArray::Impl {
public:
    Impl();
    ~Impl();

    GLuint m_vaoID {0};
    GLuint m_vboID {0};
};

VertexArray::Impl::Impl() {}

VertexArray::Impl::~Impl() {}

VertexArray::VertexArray() :
    m_d(std::make_unique<Impl>()) {
    glGenVertexArrays(1, &m_d->m_vaoID);
    glGenBuffers(1, &m_d->m_vboID);
}

VertexArray::~VertexArray() {
    glDeleteBuffers(1, &m_d->m_vboID);
    glDeleteVertexArrays(1, &m_d->m_vaoID);
}

void VertexArray::bind() const {
    glBindVertexArray(m_d->m_vaoID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::setData(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW) {
    glBindBuffer(GL_ARRAY_BUFFER, m_d->m_vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), usage);
}

void VertexArray::setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}


