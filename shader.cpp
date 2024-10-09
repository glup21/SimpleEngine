#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(string &vertexPath, string &fragmentPath)
{
    char* vertexCode = readFile(vertexPath.c_str());
    char* fragmentCode = readFile(fragmentPath.c_str());

    GLuint vertexID, fragmentID;
    compileShader(vertexID, vertexCode, GL_VERTEX_SHADER);
    compileShader(fragmentID, fragmentCode, GL_FRAGMENT_SHADER);

    //shader program

    ID = glCreateProgram();
    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);

    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Error: shader program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 

bool Shader::compileShader(GLuint &ID, char* code, int type)
{

    ID = glCreateShader(type);
    glShaderSource(ID, 1, &code, NULL);
    glCompileShader(ID);

    return checkCompileErrors(ID);

}

char* Shader::readFile(const string& filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    string line;

    while (std::getline(file, line)) {
        buffer << line << '\n';
    }

    return const_cast<char*>(buffer.str().c_str());
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