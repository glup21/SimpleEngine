#include "shaderProgram.hpp"

ShaderProgram::ShaderProgram() : ID(glCreateProgram()) {}
ShaderProgram::~ShaderProgram() { glDeleteProgram(ID); }

void ShaderProgram::attachShader(Shader* shader)
{
    glAttachShader(ID, shader->getID());
    shaders.push_back(shader);
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

void ShaderProgram::setMat4(const string& name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void ShaderProgram::setInt(const string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}