#include "renderer.h"

#include "framebuffer.h"
#include "shader_program.h"
#include "draw_object.h"

const std::string screenFragmentShaderSource = R"(
    #version 330 core
    out vec4 fragColor;
    in vec2 texCoord;

    uniform sampler2D screenTexture;

    void main() {
        fragColor = texture(screenTexture, texCoord);
    }
)";

const std::string screenVertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec2 position;
    layout(location = 1) in vec2 texCoord;

    out vec2 TexCoord;

    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
        TexCoord = texCoord;
    }
)";

class Renderer::Impl {
public:
    Impl();
    ~Impl();

    int m_width {0};
    int m_height {0};

    DrawObject m_screen;
};

Renderer::Impl::Impl() {
    m_screen.getVao().bind();
    m_screen.setShaders({
        Shader(Shader::Type::VertexShader, screenVertexShaderSource),
        Shader(Shader::Type::FragmentShader, screenFragmentShaderSource)
    });
    m_screen.setData(
        {
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f,
             1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f
        },
        {
            {0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0},
            {1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))}
        }
    );
    m_screen.getVao().unbind();
}

Renderer::Impl::~Impl() {}


Renderer::Renderer(int width, int height) : 
    m_d(std::make_unique<Impl>()) {   

    m_d->m_width = width;
    m_d->m_height = height;

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) 
        throw "Failed to initialize GLEW";

    glViewport(0, 0, width, height);
}

Renderer::~Renderer() {}

void Renderer::draw(const DrawObject & obj, const Framebuffer &target) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    obj.getProgram().use();
    obj.getVao().bind();
    obj.drawFunc();
    obj.getVao().unbind();
}

void Renderer::drawBuffer(const Framebuffer &buff) {
    glClear(GL_COLOR_BUFFER_BIT);

    m_d->m_screen.getProgram().use();
    glBindTexture(GL_TEXTURE_2D, buff.getTextureID());

    m_d->m_screen.getVao().bind();
    m_d->m_screen.drawFunc();
    m_d->m_screen.getVao().unbind();
}
