#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.hpp"
#include <glm/glm.hpp> 

class Material
{
public:
    Material();
    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess, const std::string& texturePath = "");

    glm::vec3 getAmbient() const;
    void setAmbient(const glm::vec3& ambient);

    glm::vec3 getDiffuse() const;
    void setDiffuse(const glm::vec3& diffuse);

    glm::vec3 getSpecular() const;
    void setSpecular(const glm::vec3& specular);

    float getShininess() const;
    void setShininess(float shininess);

    const Texture& getTexture() const;
    bool loadTexture(const std::string& texturePath);

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    Texture texture;
};

#endif 