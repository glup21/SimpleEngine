#include "material.hpp"
#include <iostream>

// Default constructor
Material::Material()
    : ambient(1.0f, 1.0f, 1.0f), diffuse(1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f), shininess(32.0f)
{
}

// Parameterized constructor
Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess, const std::string& texturePath)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
{
    if (!texturePath.empty()) {
        loadTexture(texturePath);
    }
}

// Getters and Setters
glm::vec3 Material::getAmbient() const
{
    return ambient;
}

void Material::setAmbient(const glm::vec3& ambient)
{
    this->ambient = ambient;
}

glm::vec3 Material::getDiffuse() const
{
    return diffuse;
}

void Material::setDiffuse(const glm::vec3& diffuse)
{
    this->diffuse = diffuse;
}

glm::vec3 Material::getSpecular() const
{
    return specular;
}

void Material::setSpecular(const glm::vec3& specular)
{
    this->specular = specular;
}

float Material::getShininess() const
{
    return shininess;
}

void Material::setShininess(float shininess)
{
    this->shininess = shininess;
}

const Texture& Material::getTexture() const
{
    return texture;
}

bool Material::loadTexture(const std::string& texturePath)
{
    return texture.loadFromFile(texturePath);
}