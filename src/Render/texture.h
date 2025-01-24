#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <memory>

class Texture {
public:
    // Конструктор: создаёт пустую текстуру
    Texture(GLenum textureTarget, int width, int height, GLenum internalFormat, GLenum format, GLenum type);

    // Деструктор: освобождает ресурсы
    ~Texture();

    // Активировать текстуру
    void Bind(GLenum textureUnit = GL_TEXTURE0) const;

    // Деактивировать текстуру
    void Unbind() const;

    // Установить текстуру в униформу
    void SetUniform(GLuint shaderProgram, const std::string& uniformName, int textureUnitIndex) const;

    // Получить ID текстуры
    GLuint GetID() const;

private:
    class Impl; // Forward declaration of the implementation class
    std::unique_ptr<Impl> m_d; // Unique pointer to the implementation
};