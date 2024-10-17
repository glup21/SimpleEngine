#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.hpp"
#include <memory>

using std::unique_ptr;

class ShaderProgram
{
private:
    vector<unique_ptr<Shader>> shaders;
    GLuint ID;

    void checkLinkErrors();

public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(unique_ptr<Shader> shader);
    void link();
    void use();


};

#endif