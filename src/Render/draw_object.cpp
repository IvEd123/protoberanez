#include "draw_object.h"
#include "shader_program.h"
#include "vertex_array.h"


class DrawObject::Impl {
public:
    Impl();
    ~Impl();

    ShaderProgram       m_program;
    VertexArray         m_vao;
    std::vector<Shader> m_shaderList;
};

DrawObject::Impl::Impl() {}

DrawObject::Impl::~Impl() {}

DrawObject::DrawObject() :
    m_d(std::make_unique<Impl>()) {}

DrawObject::~DrawObject() {}

void DrawObject::setShaders(std::initializer_list<Shader> shaderList) {
   // m_d->m_shaderList = std::move(shaderList);
    for(const auto& shader : shaderList) 
        m_d->m_program.attachShader(shader);
    m_d->m_program.link();
}

void DrawObject::setData(const std::vector<float> &data, 
                         std::initializer_list<VertexArrayAttribute> attrList) {
    m_d->m_vao.bind();
    m_d->m_vao.setData(data);
    for(const auto attr : attrList)
        m_d->m_vao.setAttribute(attr);
    m_d->m_vao.unbind();
}

const ShaderProgram &DrawObject::getProgram() const {
    return m_d->m_program;
}

const VertexArray &DrawObject::getVao() const {
    return m_d->m_vao;
}
