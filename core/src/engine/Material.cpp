#include "Material.hpp"

Material::Material(ShaderProgram* shader_program):
    shader_program(shader_program)
{
    
}

void Material::addTextures(std::vector<Texture*> textures)
{

    this->textures = textures;

}

void Material::use(glm::mat4 transformMatrix)
{
    shader_program->setMat4("transform", transformMatrix);
    shader_program->setInt("textureImage", 0);
    textures[0]->bind(0);

    shader_program->use();
}
