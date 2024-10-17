#include "shaderProgram.hpp"

ShaderProgram::ShaderProgram() : ID(glCreateProgram()) {}
ShaderProgram::~ShaderProgram() { glDeleteProgram(ID); }

void ShaderProgram::attachShader(unique_ptr<Shader> shader)
{
    glAttachShader(ID, shader->getID());
    shaders.push_back(std::move(shader));
}

void ShaderProgram::link() {
    glLinkProgram(ID);
    checkLinkErrors();
}

void ShaderProgram::use() { glUseProgram(ID); }

void ShaderProgram::checkLinkErrors()
{
    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(ID, 1024, NULL, infoLog);
        std::cout << "ERROR: SHADER LINKING ERROR: " << infoLog << std::endl;
    }

}