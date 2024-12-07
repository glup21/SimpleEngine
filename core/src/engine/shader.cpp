#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(GLenum type)
     : ID(glCreateShader(type)){}

void Shader::compile(string source)
{

    const char* code = source.c_str();
    glShaderSource(ID, 1, &code, NULL);
    glCompileShader(ID);
    checkCompileErrors();

    this->source = source;

}

GLuint Shader::getID()
{
    return ID;
}

void Shader::checkCompileErrors()
{
    GLint success;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(ID, 1024, NULL, infoLog);
        std::cout << "ERROR: SHADER COMPILATION FAILED: " << infoLog << std::endl;

    }
}

string Shader::getSource()
{
    return source;
}
