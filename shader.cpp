#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(GLenum type) : ID(glCreateShader(type)) {}

void Shader::compile(const string& source)
{

    const char* code = source.c_str();
    glShaderSource(ID, 1, &code, NULL);
    glCompileShader(ID);
    checkCompileErrors();

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

// Shader::Shader(const string &vertexPath, const string &fragmentPath)
// {

//     string vertexCode = readFile(vertexPath);
//     string fragmentCode = readFile(fragmentPath);

//     GLuint vertexID, fragmentID;
//     if (!compileShader(vertexID, vertexCode.c_str(), GL_VERTEX_SHADER) ||
//         !compileShader(fragmentID, fragmentCode.c_str(), GL_FRAGMENT_SHADER))
//     {
//         std::cerr << "Error: Shader compilation failed" << std::endl;
//         return;
//     }

//     // Shader program
//     ID = glCreateProgram();
//     glAttachShader(ID, vertexID);
//     glAttachShader(ID, fragmentID);
//     glLinkProgram(ID);

//     int success;
//     char infoLog[512];
//     glGetProgramiv(ID, GL_LINK_STATUS, &success);
//     if (!success)
//     {
//         glGetProgramInfoLog(ID, 512, NULL, infoLog);
//         std::cerr << "Error: Shader program linking failed\n" << infoLog << std::endl;
//     }

//     glDeleteShader(vertexID);
//     glDeleteShader(fragmentID);
// }

// GLuint Shader::getID() const
// {
//     return ID;
// }

// void Shader::use()
// {
//     glUseProgram(ID);
// }

// void Shader::setTransform(const string& name, mat4 value) const
// {
//     glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
// }

// void Shader::setBool(const string &name, bool value) const
// {         
//     glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
// }
// void Shader::setInt(const string &name, int value) const
// { 
//     glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
// }
// void Shader::setFloat(const string &name, float value) const
// { 
//     glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
// } 

// bool Shader::compileShader(GLuint &ID, const char* code, int type)
// {

//     ID = glCreateShader(type);
//     glShaderSource(ID, 1, &code, NULL);
//     glCompileShader(ID);

//     return checkCompileErrors(ID);

// }

// string Shader::readFile(const string& filePath)
// {
//     std::ifstream file(filePath);
//     if (!file.is_open()) {
//         std::cerr << "Error: Could not open file " << filePath << std::endl;
//         return "";
//     }

//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     return buffer.str();
// }

// bool Shader::checkCompileErrors(GLuint shader)
// {
//     GLint success;
//     GLchar infoLog[1024];
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//         std::cerr << "Error: shader compilation failed\n" << infoLog << std::endl;
//         return false;
//     }
//     return true;
// }