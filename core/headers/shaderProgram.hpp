#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.hpp"
#include <memory>

using std::unique_ptr;

class ShaderProgram
{
private:
    vector<Shader*> shaders;
    GLuint ID;

    void checkLinkErrors();

public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(Shader* shader);
    void link();
    void use();

    void setMat4(const string& name, glm::mat4 value);
    void setInt(const string& name, int value);
    void setVec3(const string& name, glm::vec3 value);


};

#endif