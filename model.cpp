#include "model.h"

#include <iostream>


Model::Model(Mesh* m, ShaderProgram* sp) : mesh(m), shaderProgram(sp), transform()
{
    //setup();
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

}

void Model::update(float delta) 
{
    
    float rotationSpeed = glm::radians(50.0f); 
    float angle = rotationSpeed * delta;
    quat incrementalRotation = glm::angleAxis(angle, vec3(0.0f, 1.0f, 0.0f)); 

    // Apply the incremental rotation
    addRotation(incrementalRotation);

    addPosition(vec4(0, 0, 1, 1) * delta) ;
    std::cout << transform.position.y << std::endl; 
}
void Model::draw()
{
    if (!mesh) {
        std::cerr << "Error: mesh is null in Model::draw" << std::endl;
        return;
    }
    shaderProgram->use();

    mat4 transformMatrix = transform.getTransformMatrix();

    
    GLint transformLoc = glGetUniformLocation(shaderProgram->getProgram(), "transform");
    if (transformLoc == -1) {
        std::cerr << "Error: could not find uniform 'transform'" << std::endl;
    } else {
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    }
    mesh->draw();

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after draw: " << err << std::endl;
    }
}
Transform Model::getTransform() const
{
    return transform;
}

void Model::setTransform(const Transform& transform)
{
    this->transform = transform;
}

void Model::setPosition(const vec3& newPosition)
{
    transform.position = newPosition;
}
void Model::setRotation(const quat& newRotation)
{
    transform.rotation = newRotation;
}
void Model::setScale(const vec3& newScale)
{
    transform.scale = newScale;
}

mat4 Model::getTransformMatrix() const
{
    return transform.getTransformMatrix();
}

void Model::addPosition(const vec3& addPosition)
{
    transform.position += addPosition;
}

void Model::addRotation(const quat& addRotation)
{
    transform.rotation = glm::normalize(addRotation * transform.rotation);
}