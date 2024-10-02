#include "shaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::attachShader(const Shader& shader)
{

}

void ShaderProgram::linkProgram()
{

}

void ShaderProgram::use()
{
}

GLuint ShaderProgram::getProgram() const
{
    return program;
}

void ShaderProgram::checkLinkErrors(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "Error: shader program linking error\n" << infoLog << std::endl;
    }
}