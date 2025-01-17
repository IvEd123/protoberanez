#include "application.h"
#include <iostream>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "../Render/renderer.h"
#include "../Render/draw_object.h"
#include "../Render/framebuffer.h"

class Initializer {
public:
    Initializer(int width, int height) {
        initSdl();
        setGlAttribs();
        try {
            createWindow(width, height);
            createContext();
            initGl(width, height);
        }
        catch(...) {
            std::cerr << "initialization error";
            exit(1);
        }
    }

    void initSdl() {
        SDL_Init(SDL_INIT_VIDEO);
    }    

    void setGlAttribs() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    }

    void createWindow(int width, int height) {
        window = SDL_CreateWindow("OpenGL", 0, 0, width, height, SDL_WINDOW_OPENGL);
        if(!window) 
            throw "window create error";
    }

    void createContext() {
        context = SDL_GL_CreateContext(window);
        if(!context) 
            throw "context create error";
    }

    void initGl(int width, int height) {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) 
            throw "Failed to initialize GLEW";

        glViewport(0, 0, width, height);
    }

    SDL_Window* window {nullptr};
    SDL_GLContext context;
};

class Application::Impl {
public:
    Impl(int width, int height);
    ~Impl();

    Initializer m_initializer;

    SDL_Window* m_window {nullptr};
    SDL_GLContext m_context;
    SDL_Event m_event;
    Renderer m_renderer;
    Framebuffer m_buff;

    DrawObject line;
};

Application::Impl::Impl(int width, int height) :
    m_initializer(width, height),
    m_renderer(width, height),
    m_buff(width, height) { 

    m_window = m_initializer.window;
    m_context = m_initializer.context;

}

Application::Impl::~Impl() {
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}

Application::Application() 
    :  m_d(std::make_unique<Impl>(800, 600)) 
{
    m_d->line.setData(
        {
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 1.0f, 0.0f
        },
        {
            {0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0},
            {1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))}
        }
    );
    m_d->line.setShaders({
        Shader(Shader::VertexShader, R"(
            #version 330 core
            layout(location = 0) in vec2 position;
            layout(location = 1) in vec3 color;

            out vec3 vertexColor;

            void main() {
                gl_Position = vec4(position, 0.0, 1.0);
                vertexColor = color;
            }
        )"),
        Shader(Shader::FragmentShader, R"(
            #version 330 core
            in vec3 vertexColor;
        
            out vec4 fragColor;

            void main() {
                fragColor = vec4(vertexColor, 1.0);
            }
        )")
    });
    m_d->line.drawFunc = [] () {
        glDrawArrays(GL_POINTS, 0, 3);  // Рисуем точки
        glDrawArrays(GL_LINES, 3, 2);  // Рисуем линии
    };
}

Application::~Application() {}

void Application::run() {
    while (true) {
        if (SDL_PollEvent(&m_d->m_event) &&  
            m_d->m_event.type == SDL_QUIT)
            break;

        m_d->m_renderer.draw(m_d->line, m_d->m_buff);
        m_d->m_renderer.drawBuffer(m_d->m_buff);
        
        SDL_GL_SwapWindow(m_d->m_window);
    }
}

