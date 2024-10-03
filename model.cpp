#include "model.h"

#include <iostream>

//Model::Model(Mesh* m, Shader* s) : mesh(m), shader(s), transform() {}

Model::Model(Mesh* m, ShaderProgram* sp) : mesh(m), shaderProgram(sp), transform()
{

}

Mesh* Model::getMesh()
{
    return mesh;
}

// Shader* Model::getShader()
// {
//     return shader;
// }

void Model::setup(ShaderProgram* sP)
{
    if (!mesh) {
        std::cerr << "Error: mesh is null in Model::setup" << std::endl;
        return;
    }
    //shaderProgram->linkProgram();
    
    mesh->setup(shaderProgram);
}

void Model::update() 
{
    printf("Update!\n");
}

void Model::draw()
{
    if (!mesh) {
        std::cerr << "Error: mesh is null in Model::draw" << std::endl;
        return;
    }

    // Use the shader program
    shaderProgram->use();
    mesh->draw();
}

Transform Model::getTransform() 
{
    return transform;
}

void Model::setTransform(const Transform& transform)
{
    this->transform = transform;
}