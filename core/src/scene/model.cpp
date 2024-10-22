#include "model.hpp"
#include <iostream>
#include <filesystem>
#include <memory> 
#include <unordered_map>
#include "defaultAssets.hpp"

namespace fs = std::filesystem;
using std::unordered_map;

unordered_map<string, Texture> texturesLoaded;

Model::Model(string ID, ShaderProgram* shaderProgram, vector<Mesh> meshes) 
    : ID(ID), transform(), IDrawableObject(shaderProgram), meshes(meshes)
{
    setup();
}
void Model::setup()
{



}

//Behaviour and render

void Model::update(float delta) 
{
    // Transform* newTransform = new Transform();
    // float speed = 180.0f*delta;
    // addRotation({0.0f, 1.0f, 0.0f}, speed);

   
}

void Model::draw()
{   
    for(u_int i = 0; i < meshes.size(); i++)
        meshes[i].draw();

}

//Transform

TransformComposite Model::getTransform() const
{
    return transform;
}

void Model::setTransform(const TransformComposite& newTransform)
{
    this->transform = newTransform;

    // Update all meshes with the new transform
    for (Mesh& mesh : meshes) {
        mesh.setTransform(newTransform);
    }
}


void Model::addPosition(const vec3& newPosition) 
{
    Transform* newTransform = new Transform();
    newTransform->translate(newPosition.x, newPosition.y, newPosition.z);
    transform.addTransform(newTransform);

    for (Mesh& mesh : meshes) {
        mesh.setTransform(transform);
    }
}

void Model::addRotation(const vec3& rotationVec, const float& angle) 
{
    Transform* newTransform = new Transform();
    newTransform->rotate(angle, rotationVec.x, rotationVec.y, rotationVec.z);
    transform.addTransform(newTransform);

    // Update all meshes with the new transform
    for (Mesh& mesh : meshes) {
        mesh.setTransform(transform);
    }
}

void Model::addScale(const vec3& newScale) 
{
    Transform* newTransform = new Transform();
    newTransform->scale(newScale.x, newScale.y, newScale.z);
    transform.addTransform(newTransform);

    // Update all meshes with the new transform
    for (Mesh& mesh : meshes) {
        mesh.setTransform(transform);
    }
}

mat4 Model::getTransformMatrix() 
{
    return transform.getTransformMatrix(); 
}

