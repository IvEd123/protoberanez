#include "framebuffer.h"

class Framebuffer::Impl {
public:
    Impl();
    ~Impl();

    GLuint m_fboId {0}; 
    GLuint m_textureId {0};
    GLuint m_rboId {0};
    int    m_width {0};
    int    m_height {0};

};

Framebuffer::Impl::Impl() {}

Framebuffer::Impl::~Impl() {}


Framebuffer::Framebuffer(int width, int height) :
    m_d(std::make_unique<Impl>()){
    // Создаём фреймбуфер
    glGenFramebuffers(1, &m_d->m_fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_d->m_fboId);

    // Создаём текстуру для хранения цвета
    glGenTextures(1, &m_d->m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_d->m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_d->m_textureId, 0);

    // Создаём рендербуфер для хранения глубины и трафарета
    glGenRenderbuffers(1, &m_d->m_rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_d->m_rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_d->m_width, m_d->m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_d->m_rboId);

    // Проверяем, что фреймбуфер корректен
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
        throw "Framebuffer is not complete!";
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_d->m_fboId);
    glDeleteTextures(1, &m_d->m_textureId);
    glDeleteRenderbuffers(1, &m_d->m_rboId);
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_d->m_fboId);
    glViewport(0, 0, m_d->m_width, m_d->m_height);
}

void Framebuffer::unbind(int screenWidth, int screenHeight) const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screenWidth, screenHeight);
}

GLuint Framebuffer::getTextureID() const {
    return m_d->m_textureId;
}
