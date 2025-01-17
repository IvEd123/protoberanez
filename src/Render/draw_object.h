#pragma once
#include <memory>
#include <functional>

#include "vertex_array.h"
#include "shader.h"

class ShaderProgram;

class DrawObject {
public:
    DrawObject();
    ~DrawObject();

    void setShaders(std::initializer_list<Shader>);
    void setData(const std::vector<float>& data, std::initializer_list<VertexArrayAttribute> attrs);
    
    const ShaderProgram& getProgram() const;
    const VertexArray& getVao() const;

    std::function<void()> drawFunc;
private:
    class Impl;
    std::unique_ptr<Impl> m_d;
};