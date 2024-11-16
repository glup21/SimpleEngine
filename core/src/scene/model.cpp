#include "model.hpp"
#include <iostream>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include "defaultAssets.hpp"
#include "position.hpp"   
#include "rotation.hpp"   
#include "scale.hpp"      

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

// Behaviour and render

void Model::update(float delta) 
{

}

void Model::draw()
{   
    for (u_int i = 0; i < meshes.size(); i++)
        meshes[i].draw();
}

// Transform

TransformComposite Model::getTransform() const
{
    return transform;
}

void Model::setTransform(const TransformComposite& newTransform)
{
    this->transform = newTransform;


    for (Mesh& mesh : meshes) {
        mesh.setTransform(newTransform);
    }
}

void Model::addPosition(const glm::vec3& newPosition) 
{
    Position* position = new Position(newPosition);
    transform.addTransform(position);

    for (Mesh& mesh : meshes) {
        mesh.setTransform(transform);
    }
}

void Model::addRotation(const glm::vec3& rotationVec, const float& angle) 
{
    Rotation* rotation = new Rotation(rotationVec, angle);
    transform.addTransform(rotation);

    for (Mesh& mesh : meshes) {
        mesh.setTransform(transform);
    }
}

void Model::addScale(const glm::vec3& newScale) 
{
    Scale* scale = new Scale(newScale);
    transform.addTransform(scale);

    for (Mesh& mesh : meshes) {
        mesh.setTransform(transform);
    }
}

glm::mat4 Model::getTransformMatrix() 
{
    return transform.getTransformMatrix(); 
}
