#include "Material.hpp"

Material::Material(ShaderProgram* shader_program, std::vector<Texture*> textures):
    shader_program(shader_program), textures(textures)
{
    
}


void Material::use(glm::mat4 transformMatrix)
{
    shaderProgram->setMat4("transform", transformMatrix);
    shaderProgram->setInt("textureImage", 0);
    textures[0]->bind(0);

    shaderProgram->use();
}
