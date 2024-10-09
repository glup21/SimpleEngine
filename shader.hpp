#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <vector>

using std::string, std::vector; 

class Shader // now its ShaderProgram with shaders inside, separate ShaderProgram class is excessive
{
public:
    Shader(string &vertexPath, string &fragmentPath);
    ~Shader();
    GLuint getID() const;
    void use();

    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;

private:
    GLuint ID;
    vector<GLuint> shaders;

    bool compileShader(GLuint &ID, char* code, int type);
    bool checkCompileErrors(GLuint shader);
    char* readFile(const string& filePath);
    
};

#endif 