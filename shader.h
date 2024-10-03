#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

using std::string; 

class Shader
{
public:
    Shader(const string& filePath, GLenum shaderType);
    ~Shader();
    GLuint getShader() const;

private:
    GLuint shader;
    string code;
    string readFile(const string& filePath);
    void checkCompileErrors(GLuint shader);
};

#endif 