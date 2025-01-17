#include "application.h"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "../Render/renderer.h"

class Application::Impl {
public:
    Impl(int width, int height);
    ~Impl();

    SDL_Window* m_window {nullptr};
    SDL_GLContext m_context;
    SDL_Event m_event;
    Renderer m_renderer;
};

Application::Impl::Impl(int width, int height) :
    m_renderer(width, height) { 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    m_window = SDL_CreateWindow("OpenGL", 0, 0, width, height, SDL_WINDOW_OPENGL);
    m_context = SDL_GL_CreateContext(m_window);
}

Application::Impl::~Impl() {
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}

Application::Application() 
    :  m_d(std::make_unique<Impl>(800, 600)) 
{}

Application::~Application() {}

void Application::run() {
    while (true) {
        if (SDL_PollEvent(&m_d->m_event) &&  
            m_d->m_event.type == SDL_QUIT)
            break;


        
        SDL_GL_SwapWindow(m_d->m_window);
    }
}

