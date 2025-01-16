#pragma once
#include <memory>

class Shader {
public:
    Shader();
    ~Shader();

private:
    class Impl;
    std::unique_ptr<Impl> m_d;

};  