#include "pointLight.hpp"
#include <cmath>
#include "position.hpp"

PointLight::PointLight() {}

void PointLight::addPosition(const vec3& newPosition) 
{
    Position* position = new Position(newPosition);
    transform.addTransform(position);
    notifyObservers();
}

mat4 PointLight::getTransformMatrix() 
{
    return transform.getTransformMatrix();
}

void PointLight::update(float delta) 
{
}
