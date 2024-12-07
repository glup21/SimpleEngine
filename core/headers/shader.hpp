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

class Shader
{
private:
    GLuint ID;
    string source;
    void checkCompileErrors();

public:
    Shader(GLenum type);
    ~Shader() = default;

    void compile(string source);
    GLuint getID();
    string getSource();

};

#endif 