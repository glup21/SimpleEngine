#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

using std::string, std::vector, glm::mat4; 

class Shader // now its ShaderProgram with shaders inside, separate ShaderProgram class is excessive
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();
    GLuint getID() const;
    void use();


    void setTransform(const string& name, mat4 value) const;
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;

private:
    GLuint ID;
    vector<GLuint> shaders;

    bool compileShader(GLuint &ID, const char* code, int type);
    bool checkCompileErrors(GLuint shader);
    string readFile(const string& filePath);
    
};

#endif 