#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const string& filePath, GLenum shaderType)
{

}

Shader::~Shader()
{
    glDeleteShader(shader);
}

GLuint Shader::getShader() const
{

}

string Shader::readFile(const string& filePath) //rewrite later
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// void Shader::checkCompileErrors(GLuint shader, string type)
// {
//     GLint success;
//     GLchar infoLog[1024];
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//         std::cerr << "ERROR::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }
// }