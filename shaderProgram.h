#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "shader.h"
#include <vector>

using std::vector;

class ShaderProgram
{
public:
    ShaderProgram();
    //ShaderProgram(vector<GLuint> new_shaders);
    ~ShaderProgram();
    void attachShader(const Shader& shader);
    void linkProgram();
    void use();
    GLuint getProgram() const;

private:
    GLuint program;
    vector<GLuint> shaders;
    void checkLinkErrors();
};

#endif 