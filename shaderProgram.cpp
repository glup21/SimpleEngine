#include "shaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
    program = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{

    for (GLuint shader : shaders)
        glDetachShader(program, shader);
    
    glDeleteProgram(program);
}

void ShaderProgram::attachShader(const Shader& shader)
{

    shaders.push_back(shader.getShader());
    glAttachShader(program, shader.getShader());


}

void ShaderProgram::linkProgram()
{
    glLinkProgram(program);
    checkLinkErrors();
}

void ShaderProgram::use()
{
    glUseProgram(program);
}

GLuint ShaderProgram::getProgram() const
{
    return program;
}

void ShaderProgram::checkLinkErrors()
{
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

GLuint ShaderProgram::getShader(int N) const
{
    return shaders.at(N);
}