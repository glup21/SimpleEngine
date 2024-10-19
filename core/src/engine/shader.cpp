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

void Shader::update()
{ 
    
    //maybe later expand it for different Publishers 
    std::cout << "Update! 1\n";

    parentShaderProgram->setMat4("viewMatrix", camera->getViewMatrix());
    parentShaderProgram->setMat4("projectionMatrix", camera->getProjectionMatrix());
    parentShaderProgram->setVec3("cameraPosition", camera->getPosition());
    // GLuint uniformID = glGetUniformLocation(ID, "viewMatrix");
    // if(uniformID != -1)
    // {
    //     std::cout << "Update! 2\n";
    //     mat4 viewMatrix = camera->getViewMatrix();
    //     glUniformMatrix4fv(uniformID, 1, GL_FALSE, &viewMatrix[0][0]);
    // }

    // uniformID = glGetUniformLocation(ID, "projectionMatrix");
    // if(uniformID != -1)
    // {
    //     mat4 projectionMatrix = camera->getProjectionMatrix();
    //     glUniformMatrix4fv(uniformID, 1, GL_FALSE, &projectionMatrix[0][0]);
    // }

    // uniformID = glGetUniformLocation(ID, "cameraPosition");

    // if(uniformID != -1)
    // {
    //     vec3 cameraPosition = camera->getPosition();
    //     glUniform3fv(uniformID, 1, &cameraPosition[0]);
    // }

}

void Shader::subscribe()
{
    camera->addSubscriber(this);
}