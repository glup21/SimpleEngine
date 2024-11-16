#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "IObserver.hpp"
#include "camera.hpp"
#include "shaderProgram.hpp"

using std::string, std::vector, glm::mat4; 

class Camera;
class ShaderProgram;

class Shader
{
private:
    Camera* camera;
    GLuint ID;
    void checkCompileErrors();
    ShaderProgram* parentShaderProgram;

public:
    Shader(GLenum type, Camera* camera);
    ~Shader() = default;

    void attachShaderProgram(ShaderProgram* parentShaderProgram);
    void compile(const string& source);
    GLuint getID();

};

#endif 