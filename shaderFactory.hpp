#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include <string>
#include "configReader.hpp"
#include <memory>
#include "shader.hpp"
using std::string, std::unique_ptr;

class ShaderFactory
{
public:
    static Shader* createShader(GLenum shaderType, const string& filePath) 
    {
        string shaderSource = loadShaderSource(filePath);
        Shader* shader = new Shader(shaderType);
        shader->compile(shaderSource);
        return shader;
    }

private:
    static string loadShaderSource(const string& filePath) 
    {
        std::ifstream file(filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

};

#endif