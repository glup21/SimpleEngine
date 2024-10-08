#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "shader.h"
#include <vector>

using std::vector;

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    void attachShader(const Shader& shader);
    void linkProgram();
    void use();
    GLuint getProgram() const;
    GLuint getShader(int N) const; //1 - vertex, 2 - fragment

private:
    GLuint program;
    vector<GLuint> shaders;
    void checkLinkErrors();
};

#endif 