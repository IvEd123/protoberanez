#include "shader_program.h"
#include "shader.h"

class ShaderProgram::Impl {
public:
    Impl();
    ~Impl();

    GLuint m_programId {0};
};

ShaderProgram::Impl::Impl() {}

ShaderProgram::Impl::~Impl() {}

ShaderProgram::ShaderProgram() : 
    m_d(std::make_unique<Impl>()) {
    m_d->m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(m_d->m_programId);
}

void ShaderProgram::attachShader(const Shader &shader){
    glAttachShader(m_d->m_programId, shader.getID());
}

void ShaderProgram::link(){
    glLinkProgram(m_d->m_programId);

    GLint success;
    glGetProgramiv(m_d->m_programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_d->m_programId, 512, nullptr, infoLog);
        //std::cerr << "Error linking program: " << infoLog << std::endl;
    }
}

void ShaderProgram::use() const {
    glUseProgram(m_d->m_programId);
}

GLuint ShaderProgram::getID() const {
    return m_d->m_programId;
}
