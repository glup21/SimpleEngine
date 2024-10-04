#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const string& filePath, GLenum shaderType)
{
    shader = glCreateShader(shaderType);
    code = readFile(filePath);
    const char* tmp = code.c_str();
    glShaderSource(shader, 1, &tmp, NULL);

}

bool Shader::compileShader()
{
    glCompileShader(shader);
    return checkCompileErrors(shader);
}

Shader::~Shader()
{
    glDeleteShader(shader);
    
}

GLuint Shader::getShader() const
{
    return shader;
}

string Shader::readFile(const string& filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    string line;

    while (std::getline(file, line)) {
        buffer << line << '\n';
    }

    return buffer.str();
}

bool Shader::checkCompileErrors(GLuint shader)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERROR COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}