#include "pointLight.hpp"
#include <cmath> 

PointLight::PointLight(ShaderProgram* shaderProgram) : shaderProgram(shaderProgram), time(0.0f)
{
}

void PointLight::addPosition(const vec3& newPosition) 
{
    Transform* newTransform = new Transform();
    newTransform->translate(newPosition.x, newPosition.y, newPosition.z);
    transform.addTransform(newTransform); 
}

mat4 PointLight::getTransformMatrix() 
{
    return transform.getTransformMatrix(); 
}

void PointLight::update(float delta)
{
    shaderProgram->setVec3("LightPosition", vec3(getTransformMatrix()[3]));

}