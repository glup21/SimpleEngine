#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"
#include "shaderProgram.hpp"
#include <memory>
#include <vector>
#include "transformComposite.hpp"

class Material
{
    ShaderProgram* shader_program;
    std::vector<Texture*> textures;

public:
    Material(ShaderProgram* shader_program);
    ~Material() = default;

    void addTextures(std::vector<Texture*> textures);
    void use(glm::mat4 transformMatrix);
    ShaderProgram* getShaderProgram(){return shader_program;}

};

#endif