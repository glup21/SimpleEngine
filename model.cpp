#include "model.h"

#include "model.h"

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
    mesh->setup();
    if(shader)
        shaderProgram->attachShader(*shader);
}

void Model::update() 
{
    printf("Update!\n");
}

void Model::draw()
{
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