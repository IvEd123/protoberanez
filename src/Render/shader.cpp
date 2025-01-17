#include "shader.h"

GLenum typeToGlenum(Shader::Type t) {
    switch (t)
    {
        case Shader::Type::VertexShader: return GL_VERTEX_SHADER;
        case Shader::Type::FragmentShader: return GL_FRAGMENT_SHADER;
    }
}

class Shader::Impl {
public:
    Impl();
    ~Impl();

    GLuint m_shaderId {0};
};

Shader::Impl::Impl() {}

Shader::Impl::~Impl() {}

Shader::Shader(Shader::Type type, const std::string& source) :
    m_d(std::make_unique<Impl>()) {
    m_d->m_shaderId = glCreateShader(typeToGlenum(type));
    const char* src = source.c_str();
    glShaderSource(m_d->m_shaderId, 1, &src, nullptr);
    glCompileShader(m_d->m_shaderId);

    GLint success;
    glGetShaderiv(m_d->m_shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_d->m_shaderId, 512, nullptr, infoLog);
        //std::cerr << "Error compiling shader: " << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(m_d->m_shaderId);
}

GLuint Shader::getID() const {
    return m_d->m_shaderId;
}
