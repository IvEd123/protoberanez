#pragma once
#include <memory>

class DrawObject;
class Framebuffer;

class Renderer {
public: 
    Renderer(int width, int height);
    ~Renderer();

    void draw(const DrawObject&, const Framebuffer& target);
    void drawBuffer(const Framebuffer& buff);

private:
    class Impl;
    std::unique_ptr<Impl> m_d;

};
