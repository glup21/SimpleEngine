#include "model.h"

#include <iostream>


Model::Model(Mesh* m, ShaderProgram* sp) : mesh(m), shaderProgram(sp), transform()
{

}

Mesh* Model::getMesh()
{
    return mesh;
}

void Model::setup(ShaderProgram* sP)
{
    if (!mesh) {
        std::cerr << "Error: mesh is null in Model::setup" << std::endl;
        return;
    } 
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