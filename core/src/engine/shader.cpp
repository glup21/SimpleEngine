#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(GLenum type, Camera* camera)
     : ID(glCreateShader(type)), camera(camera) {}

void Shader::compile(const string& source)
{

    const char* code = source.c_str();
    glShaderSource(ID, 1, &code, NULL);
    glCompileShader(ID);
    checkCompileErrors();

}

void Shader::attachShaderProgram(ShaderProgram* parentShaderProgram)
{
    this->parentShaderProgram = parentShaderProgram;
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

