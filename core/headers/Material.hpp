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
    Material(ShaderProgram* shader_program, std::vector<Texture*> textures);
    ~Material() = default;


    void use(glm::mat4 transformMatrix);

};

#endif