#include "model.h"

#include <iostream>

Model::Model(Mesh* m, Shader* s) : mesh(m), shader(s), transform() {}

Mesh* Model::getMesh()
{
    return mesh;
}

Shader* Model::getShader()
{
    return shader;
}

void Model::setup(ShaderProgram* shaderProgram)
{
    if (!mesh) {
        std::cerr << "Error: mesh is null in Model::setup" << std::endl;
        return;
    }

    mesh->setup(shaderProgram);

    if (shader) {
        shaderProgram->attachShader(*shader);
    } else {
        std::cerr << "Warning: shader is null in Model::setup" << std::endl;
    }
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