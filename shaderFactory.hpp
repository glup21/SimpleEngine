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
    static unique_ptr<Shader> createShader(GLenum shaderType, const string& filePath) 
    {
        string shaderSource = loadShaderSource(filePath);
        unique_ptr<Shader> shader = std::make_unique<Shader>(shaderType);
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