#include "model.hpp"
#include <iostream>
#include <filesystem>
#include <memory> 
#include <unordered_map>
#include "defaultAssets.hpp"

namespace fs = std::filesystem;
using std::unordered_map;

unordered_map<string, Texture> texturesLoaded;

Model::Model(string path, string ID, ShaderProgram* shaderProgram) 
    : directory(path), ID(ID), transform(), IDrawableObject(shaderProgram)
{
    setup();
}
//Loading - MOVE TO SEPARATE CLASS AND REWRITE THIS GARBAGE
void Model::setup()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(directory, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: assimp: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Set directory for texture loading
    directory = directory.substr(0, directory.find_last_of('/'));
    processNode(scene->mRootNode, scene);
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

