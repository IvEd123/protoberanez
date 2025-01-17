#pragma once

#include <memory>
#include <iostream>
#include <GL/glew.h>

class Framebuffer {
public:
    Framebuffer(int width, int height);
    ~Framebuffer();
    void bind() const;
    void unbind(int screenWidth, int screenHeight) const;
    GLuint getTextureID() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_d;
    
};
