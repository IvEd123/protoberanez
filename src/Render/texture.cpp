#include "Texture.h"


 class Texture::Impl {
    public:
        GLuint m_TextureID;
        GLenum m_TextureTarget;
        int m_Width, m_Height;

        Impl(GLenum textureTarget, int width, int height, GLenum internalFormat, GLenum format, GLenum type);
        ~Impl();
        void CreateTexture(int width, int height, GLenum internalFormat, GLenum format, GLenum type);
    };

Texture::Impl::Impl(GLenum textureTarget, int width, int height, GLenum internalFormat, GLenum format, GLenum type)
    : m_TextureID(0), m_TextureTarget(textureTarget), m_Width(width), m_Height(height) {
    CreateTexture(width, height, internalFormat, format, type);
}

Texture::Impl::~Impl() {
    glDeleteTextures(1, &m_TextureID);
}

void Texture::Impl::CreateTexture(int width, int height, GLenum internalFormat, GLenum format, GLenum type) {
    glGenTextures(1, &m_TextureID);
    glBindTexture(m_TextureTarget, m_TextureID);

    glTexImage2D(m_TextureTarget, 0, internalFormat, width, height, 0, format, type, nullptr);

    glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(m_TextureTarget, 0);
}

Texture::Texture(GLenum textureTarget, int width, int height, GLenum internalFormat, GLenum format, GLenum type)
    : m_d(std::make_unique<Impl>(textureTarget, width, height, internalFormat, format, type)) {}

Texture::~Texture() = default;

void Texture::Bind(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(m_d->m_TextureTarget, m_d->m_TextureID);
}

void Texture::Unbind() const {
    glBindTexture(m_d->m_TextureTarget, 0);
}

void Texture::SetUniform(GLuint shaderProgram, const std::string& uniformName, int textureUnitIndex) const {
     GLint uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (uniformLocation == -1) {
        std::cerr << "Warning: uniform " << uniformName << " not found in shader program." << std::endl;
        return;
    }
    glUniform1i(uniformLocation, textureUnitIndex);
}

GLuint Texture::GetID() const {
    return m_d->m_TextureID;
}